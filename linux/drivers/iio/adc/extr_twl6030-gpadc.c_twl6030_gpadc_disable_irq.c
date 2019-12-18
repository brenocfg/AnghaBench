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
 int /*<<< orphan*/  twl6030_interrupt_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl6030_gpadc_disable_irq(u8 mask)
{
	twl6030_interrupt_mask(mask, REG_INT_MSK_LINE_B);
	twl6030_interrupt_mask(mask, REG_INT_MSK_STS_B);
}