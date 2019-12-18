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
struct usb_device {int dummy; } ;
struct urb {struct u132* hcpriv; } ;
struct u132_urbq {struct urb* urb; int /*<<< orphan*/  urb_more; } ;
struct u132_udev {int dummy; } ;
struct u132_endp {int /*<<< orphan*/  urb_more; scalar_t__ queue_size; int /*<<< orphan*/  queue_last; struct urb** urb_list; } ;
struct u132 {int dummy; } ;

/* Variables and functions */
 size_t ENDP_QUEUE_MASK ; 
 scalar_t__ ENDP_QUEUE_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct u132_urbq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int queue_bulk_on_old_endpoint(struct u132 *u132, struct u132_udev *udev,
	struct urb *urb,
	struct usb_device *usb_dev, struct u132_endp *endp, u8 usb_addr,
	u8 usb_endp, u8 address)
{
	urb->hcpriv = u132;
	if (endp->queue_size++ < ENDP_QUEUE_SIZE) {
		endp->urb_list[ENDP_QUEUE_MASK & endp->queue_last++] = urb;
	} else {
		struct u132_urbq *urbq = kmalloc(sizeof(struct u132_urbq),
			GFP_ATOMIC);
		if (urbq == NULL) {
			endp->queue_size -= 1;
			return -ENOMEM;
		} else {
			list_add_tail(&urbq->urb_more, &endp->urb_more);
			urbq->urb = urb;
		}
	}
	return 0;
}