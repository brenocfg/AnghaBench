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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_sn_plat_cpei_handler () ; 

__attribute__((used)) static void sn_cpei_handler(int irq, void *devid, struct pt_regs *regs)
{
	/*
	 * this function's sole purpose is to call SAL when we receive
	 * a CE interrupt from SHUB or when the timer routine decides
	 * we need to call SAL to check for CEs.
	 */

	/* CALL SAL_LOG_CE */

	ia64_sn_plat_cpei_handler();
}