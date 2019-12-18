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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int LPCR_TC ; 
 int MSR_SF ; 
 int /*<<< orphan*/  SPA_CFG_DR ; 
 int /*<<< orphan*/  SPA_CFG_HV ; 
 int /*<<< orphan*/  SPA_CFG_PR ; 
 int /*<<< orphan*/  SPA_CFG_SF ; 
 int /*<<< orphan*/  SPA_CFG_TC ; 
 int /*<<< orphan*/  SPA_CFG_XLAT_hpt ; 
 int /*<<< orphan*/  SPA_CFG_XLAT_ror ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 int /*<<< orphan*/  TIF_32BIT ; 
 int /*<<< orphan*/  current ; 
 int mfmsr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 scalar_t__ radix_enabled () ; 
 int /*<<< orphan*/  test_tsk_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 calculate_cfg_state(bool kernel)
{
	u64 state;

	state = SPA_CFG_DR;
	if (mfspr(SPRN_LPCR) & LPCR_TC)
		state |= SPA_CFG_TC;
	if (radix_enabled())
		state |= SPA_CFG_XLAT_ror;
	else
		state |= SPA_CFG_XLAT_hpt;
	state |= SPA_CFG_HV;
	if (kernel) {
		if (mfmsr() & MSR_SF)
			state |= SPA_CFG_SF;
	} else {
		state |= SPA_CFG_PR;
		if (!test_tsk_thread_flag(current, TIF_32BIT))
			state |= SPA_CFG_SF;
	}
	return state;
}