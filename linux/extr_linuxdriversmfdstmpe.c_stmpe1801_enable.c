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
struct stmpe {int dummy; } ;

/* Variables and functions */
 unsigned int STMPE1801_MSK_INT_EN_GPIO ; 
 unsigned int STMPE1801_MSK_INT_EN_KPC ; 
 int /*<<< orphan*/  STMPE1801_REG_INT_EN_MASK_LOW ; 
 unsigned int STMPE_BLOCK_GPIO ; 
 unsigned int STMPE_BLOCK_KEYPAD ; 
 int __stmpe_set_bits (struct stmpe*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int stmpe1801_enable(struct stmpe *stmpe, unsigned int blocks,
			    bool enable)
{
	unsigned int mask = 0;
	if (blocks & STMPE_BLOCK_GPIO)
		mask |= STMPE1801_MSK_INT_EN_GPIO;

	if (blocks & STMPE_BLOCK_KEYPAD)
		mask |= STMPE1801_MSK_INT_EN_KPC;

	return __stmpe_set_bits(stmpe, STMPE1801_REG_INT_EN_MASK_LOW, mask,
				enable ? mask : 0);
}