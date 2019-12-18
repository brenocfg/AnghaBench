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
struct htc_ep_callbacks {scalar_t__ rx_refill_thresh; int /*<<< orphan*/  (* rx_refill ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct htc_endpoint {TYPE_1__* target; int /*<<< orphan*/  eid; int /*<<< orphan*/  rx_bufq; struct htc_ep_callbacks ep_cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_lock; } ;

/* Variables and functions */
 scalar_t__ get_queue_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath6kl_htc_rx_chk_water_mark(struct htc_endpoint *endpoint)
{
	struct htc_ep_callbacks ep_cb = endpoint->ep_cb;

	if (ep_cb.rx_refill_thresh > 0) {
		spin_lock_bh(&endpoint->target->rx_lock);
		if (get_queue_depth(&endpoint->rx_bufq)
		    < ep_cb.rx_refill_thresh) {
			spin_unlock_bh(&endpoint->target->rx_lock);
			ep_cb.rx_refill(endpoint->target, endpoint->eid);
			return;
		}
		spin_unlock_bh(&endpoint->target->rx_lock);
	}
}