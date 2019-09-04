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
 int /*<<< orphan*/  omap34xx_cpu_suspend (unsigned long) ; 

__attribute__((used)) static int omap34xx_do_sram_idle(unsigned long save_state)
{
	omap34xx_cpu_suspend(save_state);
	return 0;
}