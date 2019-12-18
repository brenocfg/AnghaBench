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
struct isp_device {int dummy; } ;
struct isp_csi2_device {int /*<<< orphan*/  regs1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCSI2_IRQENABLE ; 
 int /*<<< orphan*/  ISPCSI2_IRQSTATUS ; 
 int ISPCSI2_IRQSTATUS_COMPLEXIO1_ERR_IRQ ; 
 int ISPCSI2_IRQSTATUS_COMPLEXIO2_ERR_IRQ ; 
 int ISPCSI2_IRQSTATUS_CONTEXT (int /*<<< orphan*/ ) ; 
 int ISPCSI2_IRQSTATUS_ECC_CORRECTION_IRQ ; 
 int ISPCSI2_IRQSTATUS_ECC_NO_CORRECTION_IRQ ; 
 int ISPCSI2_IRQSTATUS_FIFO_OVF_IRQ ; 
 int ISPCSI2_IRQSTATUS_OCP_ERR_IRQ ; 
 int ISPCSI2_IRQSTATUS_SHORT_PACKET_IRQ ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi2_irq_status_set(struct isp_device *isp,
				struct isp_csi2_device *csi2, int enable)
{
	u32 reg;
	reg = ISPCSI2_IRQSTATUS_OCP_ERR_IRQ |
		ISPCSI2_IRQSTATUS_SHORT_PACKET_IRQ |
		ISPCSI2_IRQSTATUS_ECC_CORRECTION_IRQ |
		ISPCSI2_IRQSTATUS_ECC_NO_CORRECTION_IRQ |
		ISPCSI2_IRQSTATUS_COMPLEXIO2_ERR_IRQ |
		ISPCSI2_IRQSTATUS_COMPLEXIO1_ERR_IRQ |
		ISPCSI2_IRQSTATUS_FIFO_OVF_IRQ |
		ISPCSI2_IRQSTATUS_CONTEXT(0);
	isp_reg_writel(isp, reg, csi2->regs1, ISPCSI2_IRQSTATUS);
	if (enable)
		reg |= isp_reg_readl(isp, csi2->regs1, ISPCSI2_IRQENABLE);
	else
		reg = 0;

	isp_reg_writel(isp, reg, csi2->regs1, ISPCSI2_IRQENABLE);
}