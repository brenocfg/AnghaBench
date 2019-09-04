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
 scalar_t__ NUMBER_IRQS ; 

__attribute__((used)) static inline unsigned int hwirq_to_fiq(unsigned long hwirq)
{
	hwirq -= NUMBER_IRQS;
	/*
	 * The hwirq numbering used in this driver is:
	 *   BASE (0-7) GPU1 (32-63) GPU2 (64-95).
	 * This differ from the one used in the FIQ register:
	 *   GPU1 (0-31) GPU2 (32-63) BASE (64-71)
	 */
	if (hwirq >= 32)
		return hwirq - 32;

	return hwirq + 64;
}