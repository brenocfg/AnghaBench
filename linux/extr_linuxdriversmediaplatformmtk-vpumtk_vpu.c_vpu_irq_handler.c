#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ws; int /*<<< orphan*/  wq; } ;
struct mtk_vpu {int /*<<< orphan*/  clk; TYPE_1__ wdt; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int VPU_IPC_INT ; 
 int /*<<< orphan*/  VPU_TO_HOST ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vpu_cfg_readl (struct mtk_vpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpu_cfg_writel (struct mtk_vpu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpu_ipi_handler (struct mtk_vpu*) ; 

__attribute__((used)) static irqreturn_t vpu_irq_handler(int irq, void *priv)
{
	struct mtk_vpu *vpu = priv;
	u32 vpu_to_host;
	int ret;

	/*
	 * Clock should have been enabled already.
	 * Enable again in case vpu_ipi_send times out
	 * and has disabled the clock.
	 */
	ret = clk_enable(vpu->clk);
	if (ret) {
		dev_err(vpu->dev, "[VPU] enable clock failed %d\n", ret);
		return IRQ_NONE;
	}
	vpu_to_host = vpu_cfg_readl(vpu, VPU_TO_HOST);
	if (vpu_to_host & VPU_IPC_INT) {
		vpu_ipi_handler(vpu);
	} else {
		dev_err(vpu->dev, "vpu watchdog timeout! 0x%x", vpu_to_host);
		queue_work(vpu->wdt.wq, &vpu->wdt.ws);
	}

	/* VPU won't send another interrupt until we set VPU_TO_HOST to 0. */
	vpu_cfg_writel(vpu, 0x0, VPU_TO_HOST);
	clk_disable(vpu->clk);

	return IRQ_HANDLED;
}