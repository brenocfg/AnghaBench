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

/* Variables and functions */
 int /*<<< orphan*/  REG_INT_MSK_LINE_B ; 
 int /*<<< orphan*/  REG_INT_MSK_STS_B ; 
 int twl6030_interrupt_unmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_gpadc_enable_irq(u8 mask)
{
	int ret;

	ret = twl6030_interrupt_unmask(mask, REG_INT_MSK_LINE_B);
	if (ret < 0)
		return ret;

	ret = twl6030_interrupt_unmask(mask, REG_INT_MSK_STS_B);

	return ret;
}