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
struct mtk_vpu {int /*<<< orphan*/  vpu_mutex; int /*<<< orphan*/  wdt_refcnt; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPU_WDT_REG ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long vpu_cfg_readl (struct mtk_vpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpu_cfg_writel (struct mtk_vpu*,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpu_clock_enable(struct mtk_vpu *vpu)
{
	int ret;

	ret = clk_enable(vpu->clk);
	if (ret)
		return ret;
	/* Enable VPU watchdog */
	mutex_lock(&vpu->vpu_mutex);
	if (!vpu->wdt_refcnt++)
		vpu_cfg_writel(vpu,
			       vpu_cfg_readl(vpu, VPU_WDT_REG) | (1L << 31),
			       VPU_WDT_REG);
	mutex_unlock(&vpu->vpu_mutex);

	return ret;
}