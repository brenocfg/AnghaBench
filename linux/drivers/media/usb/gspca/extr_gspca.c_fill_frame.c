#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct urb {int number_of_packets; TYPE_2__* iso_frame_desc; scalar_t__ transfer_buffer; int /*<<< orphan*/  status; } ;
struct gspca_dev {int empty_packet; int /*<<< orphan*/  streaming; int /*<<< orphan*/  last_packet_type; TYPE_1__* sd_desc; scalar_t__ frozen; } ;
typedef  int /*<<< orphan*/  (* cam_pkt_op ) (struct gspca_dev*,int /*<<< orphan*/ *,int) ;
struct TYPE_4__ {int actual_length; int status; int offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pkt_scan ) (struct gspca_dev*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DISCARD_PACKET ; 
 int /*<<< orphan*/  D_PACK ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_frame(struct gspca_dev *gspca_dev,
			struct urb *urb)
{
	u8 *data;		/* address of data in the iso message */
	int i, len, st;
	cam_pkt_op pkt_scan;

	if (urb->status != 0) {
		if (urb->status == -ESHUTDOWN)
			return;		/* disconnection */
#ifdef CONFIG_PM
		if (gspca_dev->frozen)
			return;
#endif
		gspca_err(gspca_dev, "urb status: %d\n", urb->status);
		urb->status = 0;
		goto resubmit;
	}
	pkt_scan = gspca_dev->sd_desc->pkt_scan;
	for (i = 0; i < urb->number_of_packets; i++) {
		len = urb->iso_frame_desc[i].actual_length;

		/* check the packet status and length */
		st = urb->iso_frame_desc[i].status;
		if (st) {
			gspca_dbg(gspca_dev, D_PACK, "ISOC data error: [%d] len=%d, status=%d\n",
			       i, len, st);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			continue;
		}
		if (len == 0) {
			if (gspca_dev->empty_packet == 0)
				gspca_dev->empty_packet = 1;
			continue;
		}

		/* let the packet be analyzed by the subdriver */
		gspca_dbg(gspca_dev, D_PACK, "packet [%d] o:%d l:%d\n",
			  i, urb->iso_frame_desc[i].offset, len);
		data = (u8 *) urb->transfer_buffer
					+ urb->iso_frame_desc[i].offset;
		pkt_scan(gspca_dev, data, len);
	}

resubmit:
	if (!gspca_dev->streaming)
		return;
	/* resubmit the URB */
	st = usb_submit_urb(urb, GFP_ATOMIC);
	if (st < 0)
		pr_err("usb_submit_urb() ret %d\n", st);
}