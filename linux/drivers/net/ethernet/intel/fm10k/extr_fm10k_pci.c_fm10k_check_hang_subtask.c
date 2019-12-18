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
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
struct fm10k_q_vector {int /*<<< orphan*/  itr; TYPE_2__ rx; TYPE_1__ tx; } ;
struct fm10k_intfc {int num_tx_queues; int num_q_vectors; struct fm10k_q_vector** q_vector; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  netdev; scalar_t__ next_tx_hang_check; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int FM10K_ITR_ENABLE ; 
 int FM10K_ITR_PENDING2 ; 
 int HZ ; 
 int /*<<< orphan*/  __FM10K_DOWN ; 
 int /*<<< orphan*/  __FM10K_RESETTING ; 
 scalar_t__ jiffies ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_check_for_tx_hang (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_is_after_eq_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_check_hang_subtask(struct fm10k_intfc *interface)
{
	/* If we're down or resetting, just bail */
	if (test_bit(__FM10K_DOWN, interface->state) ||
	    test_bit(__FM10K_RESETTING, interface->state))
		return;

	/* rate limit tx hang checks to only once every 2 seconds */
	if (time_is_after_eq_jiffies(interface->next_tx_hang_check))
		return;
	interface->next_tx_hang_check = jiffies + (2 * HZ);

	if (netif_carrier_ok(interface->netdev)) {
		int i;

		/* Force detection of hung controller */
		for (i = 0; i < interface->num_tx_queues; i++)
			set_check_for_tx_hang(interface->tx_ring[i]);

		/* Rearm all in-use q_vectors for immediate firing */
		for (i = 0; i < interface->num_q_vectors; i++) {
			struct fm10k_q_vector *qv = interface->q_vector[i];

			if (!qv->tx.count && !qv->rx.count)
				continue;
			writel(FM10K_ITR_ENABLE | FM10K_ITR_PENDING2, qv->itr);
		}
	}
}