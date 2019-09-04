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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ _wakeupgen_get_irq_info (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeupgen_readl (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wakeupgen_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void _wakeupgen_set(unsigned int irq, unsigned int cpu)
{
	u32 val, bit_number;
	u8 i;

	if (_wakeupgen_get_irq_info(irq, &bit_number, &i))
		return;

	val = wakeupgen_readl(i, cpu);
	val |= BIT(bit_number);
	wakeupgen_writel(val, i, cpu);
}