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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 

__attribute__((used)) static u32 get_ccsidr(u32 csselr)
{
	u32 ccsidr;

	/* Make sure noone else changes CSSELR during this! */
	local_irq_disable();
	/* Put value into CSSELR */
	asm volatile("mcr p15, 2, %0, c0, c0, 0" : : "r" (csselr));
	isb();
	/* Read result out of CCSIDR */
	asm volatile("mrc p15, 1, %0, c0, c0, 0" : "=r" (ccsidr));
	local_irq_enable();

	return ccsidr;
}