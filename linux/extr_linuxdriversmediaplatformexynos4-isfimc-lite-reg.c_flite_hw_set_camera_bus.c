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
struct fimc_source_info {unsigned int flags; scalar_t__ sensor_bus_type; int /*<<< orphan*/  mux_id; } ;
struct fimc_lite {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ FIMC_BUS_TYPE_MIPI_CSI2 ; 
 scalar_t__ FLITE_REG_CIGCTRL ; 
 int FLITE_REG_CIGCTRL_INVPOLHREF ; 
 int FLITE_REG_CIGCTRL_INVPOLPCLK ; 
 int FLITE_REG_CIGCTRL_INVPOLVSYNC ; 
 int FLITE_REG_CIGCTRL_SELCAM_MIPI ; 
 unsigned int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 unsigned int V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 unsigned int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  flite_hw_set_camera_port (struct fimc_lite*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void flite_hw_set_camera_bus(struct fimc_lite *dev,
			     struct fimc_source_info *si)
{
	u32 cfg = readl(dev->regs + FLITE_REG_CIGCTRL);
	unsigned int flags = si->flags;

	if (si->sensor_bus_type != FIMC_BUS_TYPE_MIPI_CSI2) {
		cfg &= ~(FLITE_REG_CIGCTRL_SELCAM_MIPI |
			 FLITE_REG_CIGCTRL_INVPOLPCLK |
			 FLITE_REG_CIGCTRL_INVPOLVSYNC |
			 FLITE_REG_CIGCTRL_INVPOLHREF);

		if (flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
			cfg |= FLITE_REG_CIGCTRL_INVPOLPCLK;

		if (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
			cfg |= FLITE_REG_CIGCTRL_INVPOLVSYNC;

		if (flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
			cfg |= FLITE_REG_CIGCTRL_INVPOLHREF;
	} else {
		cfg |= FLITE_REG_CIGCTRL_SELCAM_MIPI;
	}

	writel(cfg, dev->regs + FLITE_REG_CIGCTRL);

	flite_hw_set_camera_port(dev, si->mux_id);
}