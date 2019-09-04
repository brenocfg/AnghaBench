#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usb_iso_packet_descriptor {int offset; int actual_length; scalar_t__ status; } ;
struct urb {int number_of_packets; int /*<<< orphan*/ * transfer_buffer; struct usb_iso_packet_descriptor* iso_frame_desc; int /*<<< orphan*/  status; struct ttusb* context; } ;
struct ttusb {int /*<<< orphan*/  iso_streaming; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int /*<<< orphan*/  dprintk (char*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int jiffies ; 
 int lastj ; 
 scalar_t__ numinvalid ; 
 int numpkt ; 
 scalar_t__ numsec ; 
 scalar_t__ numstuff ; 
 scalar_t__ numts ; 
 scalar_t__ time_after_eq (int,int) ; 
 int /*<<< orphan*/  ttusb_process_frame (struct ttusb*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttusb_iso_irq(struct urb *urb)
{
	struct ttusb *ttusb = urb->context;
	struct usb_iso_packet_descriptor *d;
	u8 *data;
	int len, i;

	if (!ttusb->iso_streaming)
		return;

#if 0
	printk("%s: status %d, errcount == %d, length == %i\n",
	       __func__,
	       urb->status, urb->error_count, urb->actual_length);
#endif

	if (!urb->status) {
		for (i = 0; i < urb->number_of_packets; ++i) {
			numpkt++;
			if (time_after_eq(jiffies, lastj + HZ)) {
				dprintk("frames/s: %lu (ts: %d, stuff %d, sec: %d, invalid: %d, all: %d)\n",
					numpkt * HZ / (jiffies - lastj),
					numts, numstuff, numsec, numinvalid,
					numts + numstuff + numsec + numinvalid);
				numts = numstuff = numsec = numinvalid = 0;
				lastj = jiffies;
				numpkt = 0;
			}
			d = &urb->iso_frame_desc[i];
			data = urb->transfer_buffer + d->offset;
			len = d->actual_length;
			d->actual_length = 0;
			d->status = 0;
			ttusb_process_frame(ttusb, data, len);
		}
	}
	usb_submit_urb(urb, GFP_ATOMIC);
}