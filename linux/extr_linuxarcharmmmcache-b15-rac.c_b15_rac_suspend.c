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

/* Variables and functions */
 int /*<<< orphan*/  RAC_SUSPENDED ; 
 int /*<<< orphan*/  b15_rac_disable_and_flush () ; 
 int /*<<< orphan*/  b15_rac_flags ; 
 int /*<<< orphan*/  rac_config0_reg ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b15_rac_suspend(void)
{
	/* Suspend the read-ahead cache oeprations, forcing our cache
	 * implementation to fallback to the regular ARMv7 calls.
	 *
	 * We are guaranteed to be running on the boot CPU at this point and
	 * with every other CPU quiesced, so setting RAC_SUSPENDED is not racy
	 * here.
	 */
	rac_config0_reg = b15_rac_disable_and_flush();
	set_bit(RAC_SUSPENDED, &b15_rac_flags);

	return 0;
}