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
typedef  int u32 ;
struct pistachio_gpio_bank {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_writel (struct pistachio_gpio_bank*,int,int) ; 

__attribute__((used)) static inline void gpio_mask_writel(struct pistachio_gpio_bank *bank,
				    u32 reg, unsigned int bit, u32 val)
{
	/*
	 * For most of the GPIO registers, bit 16 + X must be set in order to
	 * write bit X.
	 */
	gpio_writel(bank, (0x10000 | val) << bit, reg);
}