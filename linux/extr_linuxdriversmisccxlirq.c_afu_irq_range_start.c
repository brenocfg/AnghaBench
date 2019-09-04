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
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afu_irq_range_start(void)
{
	if (cpu_has_feature(CPU_FTR_HVMODE))
		return 1;
	return 0;
}