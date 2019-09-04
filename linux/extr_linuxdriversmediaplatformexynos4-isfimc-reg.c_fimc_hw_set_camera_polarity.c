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
struct fimc_source_info {int flags; } ;
struct fimc_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ FIMC_REG_CIGCTRL ; 
 int FIMC_REG_CIGCTRL_INVPOLFIELD ; 
 int FIMC_REG_CIGCTRL_INVPOLHREF ; 
 int FIMC_REG_CIGCTRL_INVPOLHSYNC ; 
 int FIMC_REG_CIGCTRL_INVPOLPCLK ; 
 int FIMC_REG_CIGCTRL_INVPOLVSYNC ; 
 int V4L2_MBUS_FIELD_EVEN_LOW ; 
 int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 int V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int fimc_hw_set_camera_polarity(struct fimc_dev *fimc,
				struct fimc_source_info *cam)
{
	u32 cfg = readl(fimc->regs + FIMC_REG_CIGCTRL);

	cfg &= ~(FIMC_REG_CIGCTRL_INVPOLPCLK | FIMC_REG_CIGCTRL_INVPOLVSYNC |
		 FIMC_REG_CIGCTRL_INVPOLHREF | FIMC_REG_CIGCTRL_INVPOLHSYNC |
		 FIMC_REG_CIGCTRL_INVPOLFIELD);

	if (cam->flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
		cfg |= FIMC_REG_CIGCTRL_INVPOLPCLK;

	if (cam->flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		cfg |= FIMC_REG_CIGCTRL_INVPOLVSYNC;

	if (cam->flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		cfg |= FIMC_REG_CIGCTRL_INVPOLHREF;

	if (cam->flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		cfg |= FIMC_REG_CIGCTRL_INVPOLHSYNC;

	if (cam->flags & V4L2_MBUS_FIELD_EVEN_LOW)
		cfg |= FIMC_REG_CIGCTRL_INVPOLFIELD;

	writel(cfg, fimc->regs + FIMC_REG_CIGCTRL);

	return 0;
}