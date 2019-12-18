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
struct urb {int /*<<< orphan*/  unlinked; int /*<<< orphan*/  pipe; } ;
struct u132_ring {int /*<<< orphan*/  number; } ;
struct u132_endp {size_t usb_addr; int /*<<< orphan*/  usb_endp; struct u132_ring* ring; scalar_t__ dequeueing; struct u132* u132; } ;
struct u132 {int going; int /*<<< orphan*/  scheduler_lock; TYPE_2__* platform_dev; TYPE_1__* addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int EINTR ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u132_hcd_configure_empty_recv ; 
 int /*<<< orphan*/  u132_hcd_configure_input_recv ; 
 int /*<<< orphan*/  u132_hcd_forget_urb (struct u132*,struct u132_endp*,struct urb*,int) ; 
 int /*<<< orphan*/  u132_hcd_giveback_urb (struct u132*,struct u132_endp*,struct urb*,int) ; 
 int usb_ftdi_elan_edset_input (TYPE_2__*,int /*<<< orphan*/ ,struct u132_endp*,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void u132_hcd_configure_setup_sent(void *data, struct urb *urb, u8 *buf,
	int len, int toggle_bits, int error_count, int condition_code,
	int repeat_number, int halted, int skipped, int actual, int non_null)
{
	struct u132_endp *endp = data;
	struct u132 *u132 = endp->u132;
	u8 address = u132->addr[endp->usb_addr].address;
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
		if (usb_pipein(urb->pipe)) {
			int retval;
			struct u132_ring *ring = endp->ring;
			mutex_unlock(&u132->scheduler_lock);
			retval = usb_ftdi_elan_edset_input(u132->platform_dev,
				ring->number, endp, urb, address,
				endp->usb_endp, 0,
				u132_hcd_configure_input_recv);
			if (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
			return;
		} else {
			int retval;
			struct u132_ring *ring = endp->ring;
			mutex_unlock(&u132->scheduler_lock);
			retval = usb_ftdi_elan_edset_input(u132->platform_dev,
				ring->number, endp, urb, address,
				endp->usb_endp, 0,
				u132_hcd_configure_empty_recv);
			if (retval != 0)
				u132_hcd_giveback_urb(u132, endp, urb, retval);
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