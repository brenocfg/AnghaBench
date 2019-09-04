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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ lmce_disabled; } ;

/* Variables and functions */
 int FEATURE_CONTROL_LMCE ; 
 int FEATURE_CONTROL_LOCKED ; 
 int MCG_LMCE_P ; 
 int MCG_SER_P ; 
 int /*<<< orphan*/  MSR_IA32_FEATURE_CONTROL ; 
 int /*<<< orphan*/  MSR_IA32_MCG_CAP ; 
 TYPE_1__ mca_cfg ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool lmce_supported(void)
{
	u64 tmp;

	if (mca_cfg.lmce_disabled)
		return false;

	rdmsrl(MSR_IA32_MCG_CAP, tmp);

	/*
	 * LMCE depends on recovery support in the processor. Hence both
	 * MCG_SER_P and MCG_LMCE_P should be present in MCG_CAP.
	 */
	if ((tmp & (MCG_SER_P | MCG_LMCE_P)) !=
		   (MCG_SER_P | MCG_LMCE_P))
		return false;

	/*
	 * BIOS should indicate support for LMCE by setting bit 20 in
	 * IA32_FEATURE_CONTROL without which touching MCG_EXT_CTL will
	 * generate a #GP fault.
	 */
	rdmsrl(MSR_IA32_FEATURE_CONTROL, tmp);
	if ((tmp & (FEATURE_CONTROL_LOCKED | FEATURE_CONTROL_LMCE)) ==
		   (FEATURE_CONTROL_LOCKED | FEATURE_CONTROL_LMCE))
		return true;

	return false;
}