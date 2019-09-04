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
 int /*<<< orphan*/  MCG_EXT_CTL_LMCE_EN ; 
 int /*<<< orphan*/  MSR_IA32_MCG_EXT_CTL ; 
 int /*<<< orphan*/  lmce_supported () ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_clear_lmce(void)
{
	u64 val;

	if (!lmce_supported())
		return;

	rdmsrl(MSR_IA32_MCG_EXT_CTL, val);
	val &= ~MCG_EXT_CTL_LMCE_EN;
	wrmsrl(MSR_IA32_MCG_EXT_CTL, val);
}