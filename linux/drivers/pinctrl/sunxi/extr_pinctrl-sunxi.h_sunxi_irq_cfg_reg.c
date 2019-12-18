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
typedef  int u32 ;
typedef  int u16 ;
struct sunxi_pinctrl_desc {int dummy; } ;

/* Variables and functions */
 int IRQ_CFG_IRQ_PER_REG ; 
 int IRQ_CFG_REG ; 
 int IRQ_MEM_SIZE ; 
 int IRQ_PER_BANK ; 
 int sunxi_irq_hw_bank_num (struct sunxi_pinctrl_desc const*,int) ; 

__attribute__((used)) static inline u32 sunxi_irq_cfg_reg(const struct sunxi_pinctrl_desc *desc,
				    u16 irq)
{
	u8 bank = irq / IRQ_PER_BANK;
	u8 reg = (irq % IRQ_PER_BANK) / IRQ_CFG_IRQ_PER_REG * 0x04;

	return IRQ_CFG_REG +
	       sunxi_irq_hw_bank_num(desc, bank) * IRQ_MEM_SIZE + reg;
}