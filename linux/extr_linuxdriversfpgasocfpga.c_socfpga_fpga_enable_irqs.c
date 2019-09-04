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
struct socfpga_fpga_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_INTEN_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_INTMSK_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_INTTYPE_LEVEL_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_INT_POL_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_PORTA_EOI_OFST ; 
 int /*<<< orphan*/  socfpga_fpga_writel (struct socfpga_fpga_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socfpga_fpga_enable_irqs(struct socfpga_fpga_priv *priv, u32 irqs)
{
	/* set irqs to level sensitive */
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_GPIO_INTTYPE_LEVEL_OFST, 0);

	/* set interrupt polarity */
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_GPIO_INT_POL_OFST, irqs);

	/* clear irqs */
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_GPIO_PORTA_EOI_OFST, irqs);

	/* unmask interrupts */
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_GPIO_INTMSK_OFST, 0);

	/* enable interrupts */
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_GPIO_INTEN_OFST, irqs);
}