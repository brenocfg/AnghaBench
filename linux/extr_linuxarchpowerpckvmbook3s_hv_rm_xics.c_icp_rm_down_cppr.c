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
union kvmppc_icp_state {scalar_t__ mfrr; scalar_t__ pending_pri; int need_resend; int /*<<< orphan*/  xisr; scalar_t__ cppr; } ;
typedef  scalar_t__ u8 ;
struct kvmppc_xics {int dummy; } ;
struct kvmppc_icp {int /*<<< orphan*/  n_check_resend; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 union kvmppc_icp_state READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XICS_IPI ; 
 int /*<<< orphan*/  icp_rm_check_resend (struct kvmppc_xics*,struct kvmppc_icp*) ; 
 int /*<<< orphan*/  icp_rm_try_update (struct kvmppc_icp*,union kvmppc_icp_state,union kvmppc_icp_state) ; 

__attribute__((used)) static void icp_rm_down_cppr(struct kvmppc_xics *xics, struct kvmppc_icp *icp,
			     u8 new_cppr)
{
	union kvmppc_icp_state old_state, new_state;
	bool resend;

	/*
	 * This handles several related states in one operation:
	 *
	 * ICP State: Down_CPPR
	 *
	 * Load CPPR with new value and if the XISR is 0
	 * then check for resends:
	 *
	 * ICP State: Resend
	 *
	 * If MFRR is more favored than CPPR, check for IPIs
	 * and notify ICS of a potential resend. This is done
	 * asynchronously (when used in real mode, we will have
	 * to exit here).
	 *
	 * We do not handle the complete Check_IPI as documented
	 * here. In the PAPR, this state will be used for both
	 * Set_MFRR and Down_CPPR. However, we know that we aren't
	 * changing the MFRR state here so we don't need to handle
	 * the case of an MFRR causing a reject of a pending irq,
	 * this will have been handled when the MFRR was set in the
	 * first place.
	 *
	 * Thus we don't have to handle rejects, only resends.
	 *
	 * When implementing real mode for HV KVM, resend will lead to
	 * a H_TOO_HARD return and the whole transaction will be handled
	 * in virtual mode.
	 */
	do {
		old_state = new_state = READ_ONCE(icp->state);

		/* Down_CPPR */
		new_state.cppr = new_cppr;

		/*
		 * Cut down Resend / Check_IPI / IPI
		 *
		 * The logic is that we cannot have a pending interrupt
		 * trumped by an IPI at this point (see above), so we
		 * know that either the pending interrupt is already an
		 * IPI (in which case we don't care to override it) or
		 * it's either more favored than us or non existent
		 */
		if (new_state.mfrr < new_cppr &&
		    new_state.mfrr <= new_state.pending_pri) {
			new_state.pending_pri = new_state.mfrr;
			new_state.xisr = XICS_IPI;
		}

		/* Latch/clear resend bit */
		resend = new_state.need_resend;
		new_state.need_resend = 0;

	} while (!icp_rm_try_update(icp, old_state, new_state));

	/*
	 * Now handle resend checks. Those are asynchronous to the ICP
	 * state update in HW (ie bus transactions) so we can handle them
	 * separately here as well.
	 */
	if (resend) {
		icp->n_check_resend++;
		icp_rm_check_resend(xics, icp);
	}
}