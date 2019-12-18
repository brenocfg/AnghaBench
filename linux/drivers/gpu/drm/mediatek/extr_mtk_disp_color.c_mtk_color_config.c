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
struct mtk_disp_color {int dummy; } ;
struct mtk_ddp_comp {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DISP_COLOR_HEIGHT (struct mtk_disp_color*) ; 
 scalar_t__ DISP_COLOR_WIDTH (struct mtk_disp_color*) ; 
 struct mtk_disp_color* comp_to_color (struct mtk_ddp_comp*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mtk_color_config(struct mtk_ddp_comp *comp, unsigned int w,
			     unsigned int h, unsigned int vrefresh,
			     unsigned int bpc)
{
	struct mtk_disp_color *color = comp_to_color(comp);

	writel(w, comp->regs + DISP_COLOR_WIDTH(color));
	writel(h, comp->regs + DISP_COLOR_HEIGHT(color));
}