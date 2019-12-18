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
typedef  int u32 ;
struct intel_engine_execlists {scalar_t__* active; } ;
typedef  enum csb_step { ____Placeholder_csb_step } csb_step ;

/* Variables and functions */
 int CSB_COMPLETE ; 
 int CSB_NOP ; 
 int CSB_PREEMPT ; 
 int CSB_PROMOTE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GEN12_CSB_CTX_VALID (int) ; 
 int GEN12_CTX_STATUS_SWITCHED_TO_NEW_QUEUE ; 
 int GEN12_CTX_SWITCH_DETAIL (int) ; 

__attribute__((used)) static inline enum csb_step
gen12_csb_parse(const struct intel_engine_execlists *execlists, const u32 *csb)
{
	u32 lower_dw = csb[0];
	u32 upper_dw = csb[1];
	bool ctx_to_valid = GEN12_CSB_CTX_VALID(lower_dw);
	bool ctx_away_valid = GEN12_CSB_CTX_VALID(upper_dw);
	bool new_queue = lower_dw & GEN12_CTX_STATUS_SWITCHED_TO_NEW_QUEUE;

	if (!ctx_away_valid && ctx_to_valid)
		return CSB_PROMOTE;

	/*
	 * The context switch detail is not guaranteed to be 5 when a preemption
	 * occurs, so we can't just check for that. The check below works for
	 * all the cases we care about, including preemptions of WAIT
	 * instructions and lite-restore. Preempt-to-idle via the CTRL register
	 * would require some extra handling, but we don't support that.
	 */
	if (new_queue && ctx_away_valid)
		return CSB_PREEMPT;

	/*
	 * switch detail = 5 is covered by the case above and we do not expect a
	 * context switch on an unsuccessful wait instruction since we always
	 * use polling mode.
	 */
	GEM_BUG_ON(GEN12_CTX_SWITCH_DETAIL(upper_dw));

	if (*execlists->active) {
		GEM_BUG_ON(!ctx_away_valid);
		return CSB_COMPLETE;
	}

	return CSB_NOP;
}