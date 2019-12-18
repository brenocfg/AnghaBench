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
 int COLOR_BYPASS_ALL ; 
 int COLOR_SEQ_SEL ; 
 scalar_t__ DISP_COLOR_CFG_MAIN ; 
 scalar_t__ DISP_COLOR_START (struct mtk_disp_color*) ; 
 struct mtk_disp_color* comp_to_color (struct mtk_ddp_comp*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_color_start(struct mtk_ddp_comp *comp)
{
	struct mtk_disp_color *color = comp_to_color(comp);

	writel(COLOR_BYPASS_ALL | COLOR_SEQ_SEL,
	       comp->regs + DISP_COLOR_CFG_MAIN);
	writel(0x1, comp->regs + DISP_COLOR_START(color));
}