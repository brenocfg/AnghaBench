#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usb_device {int dummy; } ;
struct urb {struct u132* hcpriv; int /*<<< orphan*/  pipe; TYPE_1__* ep; } ;
struct u132_udev {int* endp_number_in; int* endp_number_out; int enumeration; } ;
struct u132_ring {int length; struct u132_endp* curr_endp; } ;
struct TYPE_6__ {int /*<<< orphan*/  slock; } ;
struct u132_endp {int endp_number; int udev_number; int usb_addr; int usb_endp; int input; int output; int queue_size; TYPE_3__ queue_lock; scalar_t__ queue_last; struct urb** urb_list; scalar_t__ queue_next; void* pipetype; TYPE_1__* hep; struct u132* u132; scalar_t__ delayed; scalar_t__ active; scalar_t__ edset_flush; scalar_t__ dequeueing; int /*<<< orphan*/  endp_ring; struct u132_ring* ring; int /*<<< orphan*/  urb_more; int /*<<< orphan*/  scheduler; } ;
struct u132 {int num_endpoints; struct u132_udev* udev; TYPE_2__* addr; struct u132_ring* ring; struct u132_endp** endp; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {int address; } ;
struct TYPE_4__ {struct u132_endp* hcpriv; } ;

/* Variables and functions */
 size_t ENDP_QUEUE_MASK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct u132_endp*) ; 
 struct u132_endp* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  u132_endp_get_kref (struct u132*,struct u132_endp*) ; 
 int /*<<< orphan*/  u132_endp_init_kref (struct u132*,struct u132_endp*) ; 
 int /*<<< orphan*/  u132_endp_queue_work (struct u132*,struct u132_endp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u132_hcd_endp_work_scheduler ; 
 int /*<<< orphan*/  u132_to_hcd (struct u132*) ; 
 int /*<<< orphan*/  u132_udev_get_kref (struct u132*,struct u132_udev*) ; 
 int /*<<< orphan*/  u132_udev_init_kref (struct u132*,struct u132_udev*) ; 
 int usb_hcd_link_urb_to_ep (int /*<<< orphan*/ ,struct urb*) ; 
 void* usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_endpoint_and_queue_control(struct u132 *u132,
	struct urb *urb,
	struct usb_device *usb_dev, u8 usb_addr, u8 usb_endp,
	gfp_t mem_flags)
{
	struct u132_ring *ring;
	unsigned long irqs;
	int rc;
	u8 endp_number;
	struct u132_endp *endp = kmalloc(sizeof(struct u132_endp), mem_flags);

	if (!endp)
		return -ENOMEM;

	spin_lock_init(&endp->queue_lock.slock);
	spin_lock_irqsave(&endp->queue_lock.slock, irqs);
	rc = usb_hcd_link_urb_to_ep(u132_to_hcd(u132), urb);
	if (rc) {
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		kfree(endp);
		return rc;
	}

	endp_number = ++u132->num_endpoints;
	urb->ep->hcpriv = u132->endp[endp_number - 1] = endp;
	INIT_DELAYED_WORK(&endp->scheduler, u132_hcd_endp_work_scheduler);
	INIT_LIST_HEAD(&endp->urb_more);
	ring = endp->ring = &u132->ring[0];
	if (ring->curr_endp) {
		list_add_tail(&endp->endp_ring, &ring->curr_endp->endp_ring);
	} else {
		INIT_LIST_HEAD(&endp->endp_ring);
		ring->curr_endp = endp;
	}
	ring->length += 1;
	endp->dequeueing = 0;
	endp->edset_flush = 0;
	endp->active = 0;
	endp->delayed = 0;
	endp->endp_number = endp_number;
	endp->u132 = u132;
	endp->hep = urb->ep;
	u132_endp_init_kref(u132, endp);
	u132_endp_get_kref(u132, endp);
	if (usb_addr == 0) {
		u8 address = u132->addr[usb_addr].address;
		struct u132_udev *udev = &u132->udev[address];
		endp->udev_number = address;
		endp->usb_addr = usb_addr;
		endp->usb_endp = usb_endp;
		endp->input = 1;
		endp->output = 1;
		endp->pipetype = usb_pipetype(urb->pipe);
		u132_udev_init_kref(u132, udev);
		u132_udev_get_kref(u132, udev);
		udev->endp_number_in[usb_endp] = endp_number;
		udev->endp_number_out[usb_endp] = endp_number;
		urb->hcpriv = u132;
		endp->queue_size = 1;
		endp->queue_last = 0;
		endp->queue_next = 0;
		endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] = urb;
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		u132_endp_queue_work(u132, endp, 0);
		return 0;
	} else {		/*(usb_addr > 0) */
		u8 address = u132->addr[usb_addr].address;
		struct u132_udev *udev = &u132->udev[address];
		endp->udev_number = address;
		endp->usb_addr = usb_addr;
		endp->usb_endp = usb_endp;
		endp->input = 1;
		endp->output = 1;
		endp->pipetype = usb_pipetype(urb->pipe);
		u132_udev_get_kref(u132, udev);
		udev->enumeration = 2;
		udev->endp_number_in[usb_endp] = endp_number;
		udev->endp_number_out[usb_endp] = endp_number;
		urb->hcpriv = u132;
		endp->queue_size = 1;
		endp->queue_last = 0;
		endp->queue_next = 0;
		endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] = urb;
		spin_unlock_irqrestore(&endp->queue_lock.slock, irqs);
		u132_endp_queue_work(u132, endp, 0);
		return 0;
	}
}