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
 scalar_t__ DISP_REG_OVL_ROI_BGCLR ; 
 scalar_t__ DISP_REG_OVL_ROI_SIZE ; 
 scalar_t__ DISP_REG_OVL_RST ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void mtk_ovl_config(struct mtk_ddp_comp *comp, unsigned int w,
			   unsigned int h, unsigned int vrefresh,
			   unsigned int bpc)
{
	if (w != 0 && h != 0)
		writel_relaxed(h << 16 | w, comp->regs + DISP_REG_OVL_ROI_SIZE);
	writel_relaxed(0x0, comp->regs + DISP_REG_OVL_ROI_BGCLR);

	writel(0x1, comp->regs + DISP_REG_OVL_RST);
	writel(0x0, comp->regs + DISP_REG_OVL_RST);
}