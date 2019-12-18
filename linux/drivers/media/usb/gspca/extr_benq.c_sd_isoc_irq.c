#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct urb {int status; int number_of_packets; TYPE_1__* iso_frame_desc; scalar_t__ transfer_buffer; scalar_t__ context; } ;
struct gspca_dev {void* last_packet_type; struct urb** urb; scalar_t__ frozen; int /*<<< orphan*/  streaming; } ;
struct TYPE_2__ {scalar_t__ actual_length; int status; int offset; } ;

/* Variables and functions */
 void* DISCARD_PACKET ; 
 int /*<<< orphan*/  D_PACK ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 scalar_t__ SD_PKT_SZ ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_isoc_irq(struct urb *urb)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *) urb->context;
	struct urb *urb0;
	u8 *data;
	int i, st;

	gspca_dbg(gspca_dev, D_PACK, "sd isoc irq\n");
	if (!gspca_dev->streaming)
		return;
	if (urb->status != 0) {
		if (urb->status == -ESHUTDOWN)
			return;		/* disconnection */
#ifdef CONFIG_PM
		if (gspca_dev->frozen)
			return;
#endif
		pr_err("urb status: %d\n", urb->status);
		return;
	}

	/* if this is a control URN (ep 0x83), wait */
	if (urb == gspca_dev->urb[0] || urb == gspca_dev->urb[2])
		return;

	/* scan both received URBs */
	if (urb == gspca_dev->urb[1])
		urb0 = gspca_dev->urb[0];
	else
		urb0 = gspca_dev->urb[2];
	for (i = 0; i < urb->number_of_packets; i++) {

		/* check the packet status and length */
		if (urb0->iso_frame_desc[i].actual_length != SD_PKT_SZ
		    || urb->iso_frame_desc[i].actual_length != SD_PKT_SZ) {
			gspca_err(gspca_dev, "ISOC bad lengths %d / %d\n",
				  urb0->iso_frame_desc[i].actual_length,
				  urb->iso_frame_desc[i].actual_length);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			continue;
		}
		st = urb0->iso_frame_desc[i].status;
		if (st == 0)
			st = urb->iso_frame_desc[i].status;
		if (st) {
			pr_err("ISOC data error: [%d] status=%d\n",
				i, st);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			continue;
		}

		/*
		 * The images are received in URBs of different endpoints
		 * (0x83 and 0x82).
		 * Image pieces in URBs of ep 0x83 are continuated in URBs of
		 * ep 0x82 of the same index.
		 * The packets in the URBs of endpoint 0x83 start with:
		 *	- 80 ba/bb 00 00 = start of image followed by 'ff d8'
		 *	- 04 ba/bb oo oo = image piece
		 *		where 'oo oo' is the image offset
						(not checked)
		 *	- (other -> bad frame)
		 * The images are JPEG encoded with full header and
		 * normal ff escape.
		 * The end of image ('ff d9') may occur in any URB.
		 * (not checked)
		 */
		data = (u8 *) urb0->transfer_buffer
					+ urb0->iso_frame_desc[i].offset;
		if (data[0] == 0x80 && (data[1] & 0xfe) == 0xba) {

			/* new image */
			gspca_frame_add(gspca_dev, LAST_PACKET,
					NULL, 0);
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					data + 4, SD_PKT_SZ - 4);
		} else if (data[0] == 0x04 && (data[1] & 0xfe) == 0xba) {
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data + 4, SD_PKT_SZ - 4);
		} else {
			gspca_dev->last_packet_type = DISCARD_PACKET;
			continue;
		}
		data = (u8 *) urb->transfer_buffer
					+ urb->iso_frame_desc[i].offset;
		gspca_frame_add(gspca_dev, INTER_PACKET,
				data, SD_PKT_SZ);
	}

	/* resubmit the URBs */
	st = usb_submit_urb(urb0, GFP_ATOMIC);
	if (st < 0)
		pr_err("usb_submit_urb(0) ret %d\n", st);
	st = usb_submit_urb(urb, GFP_ATOMIC);
	if (st < 0)
		pr_err("usb_submit_urb() ret %d\n", st);
}