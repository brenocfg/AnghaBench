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
struct mtk_ddp_comp {scalar_t__ regs; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 scalar_t__ DISP_REG_OVL_RDMA_CTRL (unsigned int) ; 
 scalar_t__ DISP_REG_OVL_RDMA_GMC (unsigned int) ; 
 scalar_t__ DISP_REG_OVL_SRC_CON ; 
 unsigned int OVL_RDMA_MEM_GMC ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mtk_ovl_layer_on(struct mtk_ddp_comp *comp, unsigned int idx)
{
	unsigned int reg;

	writel(0x1, comp->regs + DISP_REG_OVL_RDMA_CTRL(idx));
	writel(OVL_RDMA_MEM_GMC, comp->regs + DISP_REG_OVL_RDMA_GMC(idx));

	reg = readl(comp->regs + DISP_REG_OVL_SRC_CON);
	reg = reg | BIT(idx);
	writel(reg, comp->regs + DISP_REG_OVL_SRC_CON);
}