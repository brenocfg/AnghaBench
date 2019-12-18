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
struct mmphw_ctrl {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ LCD_TOP_CTRL ; 
 scalar_t__ SPU_IRQ_ENA ; 
 int err_imask (int) ; 
 int path_imasks (int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void ctrl_set_default(struct mmphw_ctrl *ctrl)
{
	u32 tmp, irq_mask;

	/*
	 * LCD Global control(LCD_TOP_CTRL) should be configed before
	 * any other LCD registers read/write, or there maybe issues.
	 */
	tmp = readl_relaxed(ctrl->reg_base + LCD_TOP_CTRL);
	tmp |= 0xfff0;
	writel_relaxed(tmp, ctrl->reg_base + LCD_TOP_CTRL);


	/* disable all interrupts */
	irq_mask = path_imasks(0) | err_imask(0) |
		   path_imasks(1) | err_imask(1);
	tmp = readl_relaxed(ctrl->reg_base + SPU_IRQ_ENA);
	tmp &= ~irq_mask;
	tmp |= irq_mask;
	writel_relaxed(tmp, ctrl->reg_base + SPU_IRQ_ENA);
}