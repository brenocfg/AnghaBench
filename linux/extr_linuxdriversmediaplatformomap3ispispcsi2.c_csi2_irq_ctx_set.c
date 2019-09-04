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
struct isp_device {int dummy; } ;
struct isp_csi2_device {int /*<<< orphan*/  regs1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCSI2_CTX_IRQENABLE (int) ; 
 int /*<<< orphan*/  ISPCSI2_CTX_IRQSTATUS (int) ; 
 int /*<<< orphan*/  ISPCSI2_CTX_IRQSTATUS_FE_IRQ ; 
 int /*<<< orphan*/  isp_reg_clr (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi2_irq_ctx_set(struct isp_device *isp,
			     struct isp_csi2_device *csi2, int enable)
{
	int i;

	for (i = 0; i < 8; i++) {
		isp_reg_writel(isp, ISPCSI2_CTX_IRQSTATUS_FE_IRQ, csi2->regs1,
			       ISPCSI2_CTX_IRQSTATUS(i));
		if (enable)
			isp_reg_set(isp, csi2->regs1, ISPCSI2_CTX_IRQENABLE(i),
				    ISPCSI2_CTX_IRQSTATUS_FE_IRQ);
		else
			isp_reg_clr(isp, csi2->regs1, ISPCSI2_CTX_IRQENABLE(i),
				    ISPCSI2_CTX_IRQSTATUS_FE_IRQ);
	}
}