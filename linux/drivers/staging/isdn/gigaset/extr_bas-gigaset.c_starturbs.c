#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct urb {int number_of_packets; TYPE_5__* iso_frame_desc; void* transfer_flags; } ;
struct TYPE_10__ {struct bas_bc_state* bas; } ;
struct bc_state {scalar_t__ proto2; int channel; int limit; struct urb* urb; int /*<<< orphan*/  inputstate; TYPE_4__ hw; TYPE_3__* cs; } ;
struct bas_bc_state {int running; int /*<<< orphan*/ * isooutovfl; int /*<<< orphan*/  isooutdone; struct bc_state* isoouturbs; struct bc_state* isooutfree; TYPE_6__* isooutbuf; scalar_t__ isoinbuf; struct urb** isoinurbs; } ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_11__ {int offset; int length; scalar_t__ actual_length; scalar_t__ status; } ;
struct TYPE_8__ {TYPE_1__* bas; } ;
struct TYPE_9__ {TYPE_2__ hw; } ;
struct TYPE_7__ {struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAS_FRAMETIME ; 
 int BAS_INBUFSIZE ; 
 int BAS_INURBS ; 
 int BAS_MAXFRAME ; 
 int BAS_NORMFRAME ; 
 int BAS_NUMFRAMES ; 
 int BAS_OUTBUFSIZE ; 
 int BAS_OUTURBS ; 
 int /*<<< orphan*/  DEBUG_ISO ; 
 int EFAULT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INS_flag_hunt ; 
 scalar_t__ L2_HDLC ; 
 int /*<<< orphan*/  PPP_FLAG ; 
 void* URB_ISO_ASAP ; 
 int /*<<< orphan*/  dump_urb (int /*<<< orphan*/ ,char*,struct urb*) ; 
 int /*<<< orphan*/  gigaset_isowbuf_init (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_iso_callback ; 
 int /*<<< orphan*/  stopurbs (struct bas_bc_state*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,struct bc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_sndisocpipe (struct usb_device*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_iso_callback ; 

__attribute__((used)) static int starturbs(struct bc_state *bcs)
{
	struct usb_device *udev = bcs->cs->hw.bas->udev;
	struct bas_bc_state *ubc = bcs->hw.bas;
	struct urb *urb;
	int j, k;
	int rc;

	/* initialize L2 reception */
	if (bcs->proto2 == L2_HDLC)
		bcs->inputstate |= INS_flag_hunt;

	/* submit all isochronous input URBs */
	ubc->running = 1;
	for (k = 0; k < BAS_INURBS; k++) {
		urb = ubc->isoinurbs[k];
		if (!urb) {
			rc = -EFAULT;
			goto error;
		}
		usb_fill_int_urb(urb, udev,
				 usb_rcvisocpipe(udev, 3 + 2 * bcs->channel),
				 ubc->isoinbuf + k * BAS_INBUFSIZE,
				 BAS_INBUFSIZE, read_iso_callback, bcs,
				 BAS_FRAMETIME);

		urb->transfer_flags = URB_ISO_ASAP;
		urb->number_of_packets = BAS_NUMFRAMES;
		for (j = 0; j < BAS_NUMFRAMES; j++) {
			urb->iso_frame_desc[j].offset = j * BAS_MAXFRAME;
			urb->iso_frame_desc[j].length = BAS_MAXFRAME;
			urb->iso_frame_desc[j].status = 0;
			urb->iso_frame_desc[j].actual_length = 0;
		}

		dump_urb(DEBUG_ISO, "Initial isoc read", urb);
		rc = usb_submit_urb(urb, GFP_ATOMIC);
		if (rc != 0)
			goto error;
	}

	/* initialize L2 transmission */
	gigaset_isowbuf_init(ubc->isooutbuf, PPP_FLAG);

	/* set up isochronous output URBs for flag idling */
	for (k = 0; k < BAS_OUTURBS; ++k) {
		urb = ubc->isoouturbs[k].urb;
		if (!urb) {
			rc = -EFAULT;
			goto error;
		}
		usb_fill_int_urb(urb, udev,
				 usb_sndisocpipe(udev, 4 + 2 * bcs->channel),
				 ubc->isooutbuf->data,
				 sizeof(ubc->isooutbuf->data),
				 write_iso_callback, &ubc->isoouturbs[k],
				 BAS_FRAMETIME);

		urb->transfer_flags = URB_ISO_ASAP;
		urb->number_of_packets = BAS_NUMFRAMES;
		for (j = 0; j < BAS_NUMFRAMES; ++j) {
			urb->iso_frame_desc[j].offset = BAS_OUTBUFSIZE;
			urb->iso_frame_desc[j].length = BAS_NORMFRAME;
			urb->iso_frame_desc[j].status = 0;
			urb->iso_frame_desc[j].actual_length = 0;
		}
		ubc->isoouturbs[k].limit = -1;
	}

	/* keep one URB free, submit the others */
	for (k = 0; k < BAS_OUTURBS - 1; ++k) {
		dump_urb(DEBUG_ISO, "Initial isoc write", urb);
		rc = usb_submit_urb(ubc->isoouturbs[k].urb, GFP_ATOMIC);
		if (rc != 0)
			goto error;
	}
	dump_urb(DEBUG_ISO, "Initial isoc write (free)", urb);
	ubc->isooutfree = &ubc->isoouturbs[BAS_OUTURBS - 1];
	ubc->isooutdone = ubc->isooutovfl = NULL;
	return 0;
error:
	stopurbs(ubc);
	return rc;
}