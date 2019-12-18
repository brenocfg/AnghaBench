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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sunxi_pinctrl_desc {int dummy; } ;

/* Variables and functions */
 int IRQ_PER_BANK ; 
 int /*<<< orphan*/  sunxi_irq_status_reg_from_bank (struct sunxi_pinctrl_desc const*,int) ; 

__attribute__((used)) static inline u32 sunxi_irq_status_reg(const struct sunxi_pinctrl_desc *desc,
				       u16 irq)
{
	u8 bank = irq / IRQ_PER_BANK;

	return sunxi_irq_status_reg_from_bank(desc, bank);
}