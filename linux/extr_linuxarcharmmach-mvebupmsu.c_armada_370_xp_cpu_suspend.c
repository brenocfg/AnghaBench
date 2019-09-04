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
 int /*<<< orphan*/  armada_370_xp_pmsu_idle_enter ; 
 int cpu_suspend (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada_370_xp_cpu_suspend(unsigned long deepidle)
{
	return cpu_suspend(deepidle, armada_370_xp_pmsu_idle_enter);
}