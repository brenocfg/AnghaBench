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
typedef  size_t u8 ;
struct urb {size_t* transfer_buffer; int actual_length; scalar_t__ transfer_buffer_length; int transfer_flags; int /*<<< orphan*/  unlinked; int /*<<< orphan*/  interval; } ;
struct u132_udev {int /*<<< orphan*/  usb_device; } ;
struct u132_ring {scalar_t__ in_use; } ;
struct u132_endp {size_t usb_addr; int toggle_bits; int /*<<< orphan*/  usb_endp; scalar_t__ jiffies; scalar_t__ active; struct u132_ring* ring; scalar_t__ dequeueing; struct u132* u132; } ;
struct u132 {int going; int /*<<< orphan*/  scheduler_lock; TYPE_2__* platform_dev; struct u132_udev* udev; TYPE_1__* addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {size_t address; } ;

/* Variables and functions */
 int EINTR ; 
 int ENODEV ; 
 int TD_CC_NOERROR ; 
 int TD_CC_STALL ; 
 int TD_DATAUNDERRUN ; 
 int URB_SHORT_NOT_OK ; 
 int* cc_to_error ; 
 int /*<<< orphan*/ * cc_to_text ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int edset_single (struct u132*,struct u132_ring*,struct u132_endp*,struct urb*,size_t,int,void (*) (void*,struct urb*,size_t*,int,int,int,int,int,int,int,int,int)) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u132_endp_put_kref (struct u132*,struct u132_endp*) ; 
 int /*<<< orphan*/  u132_hcd_forget_urb (struct u132*,struct u132_endp*,struct urb*,int) ; 
 int /*<<< orphan*/  u132_hcd_giveback_urb (struct u132*,struct u132_endp*,struct urb*,int) ; 
 int /*<<< orphan*/  u132_ring_cancel_work (struct u132*,struct u132_ring*) ; 
 int /*<<< orphan*/  u132_ring_queue_work (struct u132*,struct u132_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_settoggle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void u132_hcd_interrupt_recv(void *data, struct urb *urb, u8 *buf,
	int len, int toggle_bits, int error_count, int condition_code,
	int repeat_number, int halted, int skipped, int actual, int non_null)
{
	struct u132_endp *endp = data;
	struct u132 *u132 = endp->u132;
	u8 address = u132->addr[endp->usb_addr].address;
	struct u132_udev *udev = &u132->udev[address];
	mutex_lock(&u132->scheduler_lock);
	if (u132->going > 1) {
		dev_err(&u132->platform_dev->dev, "device has been removed %d\n"
			, u132->going);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_forget_urb(u132, endp, urb, -ENODEV);
		return;
	} else if (endp->dequeueing) {
		endp->dequeueing = 0;
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -EINTR);
		return;
	} else if (u132->going > 0) {
		dev_err(&u132->platform_dev->dev, "device is being removed "
				"urb=%p\n", urb);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, -ENODEV);
		return;
	} else if (!urb->unlinked) {
		struct u132_ring *ring = endp->ring;
		u8 *u = urb->transfer_buffer + urb->actual_length;
		u8 *b = buf;
		int L = len;

		while (L-- > 0)
			*u++ = *b++;

		urb->actual_length += len;
		if ((condition_code == TD_CC_NOERROR) &&
			(urb->transfer_buffer_length > urb->actual_length)) {
			endp->toggle_bits = toggle_bits;
			usb_settoggle(udev->usb_device, endp->usb_endp, 0,
				1 & toggle_bits);
			if (urb->actual_length > 0) {
				int retval;
				mutex_unlock(&u132->scheduler_lock);
				retval = edset_single(u132, ring, endp, urb,
					address, endp->toggle_bits,
					u132_hcd_interrupt_recv);
				if (retval != 0)
					u132_hcd_giveback_urb(u132, endp, urb,
						retval);
			} else {
				ring->in_use = 0;
				endp->active = 0;
				endp->jiffies = jiffies +
					msecs_to_jiffies(urb->interval);
				u132_ring_cancel_work(u132, ring);
				u132_ring_queue_work(u132, ring, 0);
				mutex_unlock(&u132->scheduler_lock);
				u132_endp_put_kref(u132, endp);
			}
			return;
		} else if ((condition_code == TD_DATAUNDERRUN) &&
			((urb->transfer_flags & URB_SHORT_NOT_OK) == 0)) {
			endp->toggle_bits = toggle_bits;
			usb_settoggle(udev->usb_device, endp->usb_endp, 0,
				1 & toggle_bits);
			mutex_unlock(&u132->scheduler_lock);
			u132_hcd_giveback_urb(u132, endp, urb, 0);
			return;
		} else {
			if (condition_code == TD_CC_NOERROR) {
				endp->toggle_bits = toggle_bits;
				usb_settoggle(udev->usb_device, endp->usb_endp,
					0, 1 & toggle_bits);
			} else if (condition_code == TD_CC_STALL) {
				endp->toggle_bits = 0x2;
				usb_settoggle(udev->usb_device, endp->usb_endp,
					0, 0);
			} else {
				endp->toggle_bits = 0x2;
				usb_settoggle(udev->usb_device, endp->usb_endp,
					0, 0);
				dev_err(&u132->platform_dev->dev, "urb=%p givin"
					"g back INTERRUPT %s\n", urb,
					cc_to_text[condition_code]);
			}
			mutex_unlock(&u132->scheduler_lock);
			u132_hcd_giveback_urb(u132, endp, urb,
				cc_to_error[condition_code]);
			return;
		}
	} else {
		dev_err(&u132->platform_dev->dev, "CALLBACK called urb=%p "
				"unlinked=%d\n", urb, urb->unlinked);
		mutex_unlock(&u132->scheduler_lock);
		u132_hcd_giveback_urb(u132, endp, urb, 0);
		return;
	}
}