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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_hw_ce_host_wm_regs {int /*<<< orphan*/  wm_mask; int /*<<< orphan*/  cc_mask; } ;
struct ath10k_ce_pipe {int /*<<< orphan*/  (* send_cb ) (struct ath10k_ce_pipe*) ;int /*<<< orphan*/  (* recv_cb ) (struct ath10k_ce_pipe*) ;int /*<<< orphan*/  ctrl_addr; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; struct ath10k_ce_pipe* ce_states; } ;
struct ath10k {TYPE_1__* hw_ce_regs; } ;
struct TYPE_2__ {struct ath10k_hw_ce_host_wm_regs* wm_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_ce_engine_int_status_clear (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ath10k_ce_pipe*) ; 
 int /*<<< orphan*/  stub2 (struct ath10k_ce_pipe*) ; 

void ath10k_ce_per_engine_service(struct ath10k *ar, unsigned int ce_id)
{
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	struct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	struct ath10k_hw_ce_host_wm_regs *wm_regs = ar->hw_ce_regs->wm_regs;
	u32 ctrl_addr = ce_state->ctrl_addr;

	spin_lock_bh(&ce->ce_lock);

	/* Clear the copy-complete interrupts that will be handled here. */
	ath10k_ce_engine_int_status_clear(ar, ctrl_addr,
					  wm_regs->cc_mask);

	spin_unlock_bh(&ce->ce_lock);

	if (ce_state->recv_cb)
		ce_state->recv_cb(ce_state);

	if (ce_state->send_cb)
		ce_state->send_cb(ce_state);

	spin_lock_bh(&ce->ce_lock);

	/*
	 * Misc CE interrupts are not being handled, but still need
	 * to be cleared.
	 */
	ath10k_ce_engine_int_status_clear(ar, ctrl_addr, wm_regs->wm_mask);

	spin_unlock_bh(&ce->ce_lock);
}