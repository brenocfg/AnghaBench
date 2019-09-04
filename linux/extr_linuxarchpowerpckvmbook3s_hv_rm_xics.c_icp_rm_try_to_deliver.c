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
union kvmppc_icp_state {scalar_t__ cppr; scalar_t__ mfrr; scalar_t__ pending_pri; int need_resend; int /*<<< orphan*/  xisr; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct kvmppc_icp {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 union kvmppc_icp_state READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icp_rm_try_update (struct kvmppc_icp*,union kvmppc_icp_state,union kvmppc_icp_state) ; 

__attribute__((used)) static bool icp_rm_try_to_deliver(struct kvmppc_icp *icp, u32 irq, u8 priority,
			       u32 *reject)
{
	union kvmppc_icp_state old_state, new_state;
	bool success;

	do {
		old_state = new_state = READ_ONCE(icp->state);

		*reject = 0;

		/* See if we can deliver */
		success = new_state.cppr > priority &&
			new_state.mfrr > priority &&
			new_state.pending_pri > priority;

		/*
		 * If we can, check for a rejection and perform the
		 * delivery
		 */
		if (success) {
			*reject = new_state.xisr;
			new_state.xisr = irq;
			new_state.pending_pri = priority;
		} else {
			/*
			 * If we failed to deliver we set need_resend
			 * so a subsequent CPPR state change causes us
			 * to try a new delivery.
			 */
			new_state.need_resend = true;
		}

	} while (!icp_rm_try_update(icp, old_state, new_state));

	return success;
}