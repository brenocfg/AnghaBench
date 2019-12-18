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
struct vudc {int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  ud; } ;
struct urbp {int dummy; } ;
struct tx_item {int /*<<< orphan*/  tx_entry; struct urbp* s; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TX_SUBMIT ; 
 int /*<<< orphan*/  VDEV_EVENT_ERROR_MALLOC ; 
 struct tx_item* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void v_enqueue_ret_submit(struct vudc *udc, struct urbp *urb_p)
{
	struct tx_item *txi;

	txi = kzalloc(sizeof(*txi), GFP_ATOMIC);
	if (!txi) {
		usbip_event_add(&udc->ud, VDEV_EVENT_ERROR_MALLOC);
		return;
	}

	txi->type = TX_SUBMIT;
	txi->s = urb_p;

	list_add_tail(&txi->tx_entry, &udc->tx_queue);
}