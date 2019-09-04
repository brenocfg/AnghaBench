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
struct socfpga_fpga_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_INTEN_OFST ; 
 int /*<<< orphan*/  socfpga_fpga_writel (struct socfpga_fpga_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socfpga_fpga_disable_irqs(struct socfpga_fpga_priv *priv)
{
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_GPIO_INTEN_OFST, 0);
}