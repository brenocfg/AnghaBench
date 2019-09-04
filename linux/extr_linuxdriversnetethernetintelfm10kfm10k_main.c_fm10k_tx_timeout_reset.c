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
struct fm10k_intfc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_timeout_count; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_FLAG_RESET_REQUESTED ; 
 int /*<<< orphan*/  __FM10K_DOWN ; 
 int /*<<< orphan*/  fm10k_service_event_schedule (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fm10k_tx_timeout_reset(struct fm10k_intfc *interface)
{
	/* Do the reset outside of interrupt context */
	if (!test_bit(__FM10K_DOWN, interface->state)) {
		interface->tx_timeout_count++;
		set_bit(FM10K_FLAG_RESET_REQUESTED, interface->flags);
		fm10k_service_event_schedule(interface);
	}
}