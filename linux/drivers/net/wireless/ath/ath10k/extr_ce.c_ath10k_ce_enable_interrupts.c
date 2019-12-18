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
struct ath10k_ce_pipe {int attr_flags; } ;
struct ath10k_ce {struct ath10k_ce_pipe* ce_states; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int CE_ATTR_POLL ; 
 int CE_COUNT ; 
 int /*<<< orphan*/  ath10k_ce_per_engine_handler_adjust (struct ath10k_ce_pipe*) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 

void ath10k_ce_enable_interrupts(struct ath10k *ar)
{
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	int ce_id;
	struct ath10k_ce_pipe *ce_state;

	/* Enable interrupts for copy engine that
	 * are not using polling mode.
	 */
	for (ce_id = 0; ce_id < CE_COUNT; ce_id++) {
		ce_state  = &ce->ce_states[ce_id];
		if (ce_state->attr_flags & CE_ATTR_POLL)
			continue;

		ath10k_ce_per_engine_handler_adjust(ce_state);
	}
}