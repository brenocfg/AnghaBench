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
struct stmpe {int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 unsigned int STMPE811_SYS_CTRL2_ADC_OFF ; 
 unsigned int STMPE811_SYS_CTRL2_GPIO_OFF ; 
 unsigned int STMPE811_SYS_CTRL2_TSC_OFF ; 
 unsigned int STMPE_BLOCK_ADC ; 
 unsigned int STMPE_BLOCK_GPIO ; 
 unsigned int STMPE_BLOCK_TOUCHSCREEN ; 
 size_t STMPE_IDX_SYS_CTRL2 ; 
 int __stmpe_set_bits (struct stmpe*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int stmpe811_enable(struct stmpe *stmpe, unsigned int blocks,
			   bool enable)
{
	unsigned int mask = 0;

	if (blocks & STMPE_BLOCK_GPIO)
		mask |= STMPE811_SYS_CTRL2_GPIO_OFF;

	if (blocks & STMPE_BLOCK_ADC)
		mask |= STMPE811_SYS_CTRL2_ADC_OFF;

	if (blocks & STMPE_BLOCK_TOUCHSCREEN)
		mask |= STMPE811_SYS_CTRL2_TSC_OFF;

	return __stmpe_set_bits(stmpe, stmpe->regs[STMPE_IDX_SYS_CTRL2], mask,
				enable ? 0 : mask);
}