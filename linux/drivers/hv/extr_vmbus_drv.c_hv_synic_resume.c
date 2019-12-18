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
 int /*<<< orphan*/  hv_synic_enable_regs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hv_synic_resume(void)
{
	hv_synic_enable_regs(0);

	/*
	 * Note: we don't need to call hv_stimer_init(0), because the timer
	 * on CPU0 is not unbound in hv_synic_suspend(), and the timer is
	 * automatically re-enabled in timekeeping_resume().
	 */
}