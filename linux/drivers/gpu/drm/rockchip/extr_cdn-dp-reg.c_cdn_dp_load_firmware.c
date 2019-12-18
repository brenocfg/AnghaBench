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
struct cdn_dp_device {int fw_version; int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ADDR_DMEM ; 
 scalar_t__ ADDR_IMEM ; 
 scalar_t__ APB_CTRL ; 
 int APB_DRAM_PATH ; 
 int APB_IRAM_PATH ; 
 int APB_XT_RESET ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FW_ALIVE_TIMEOUT_US ; 
 scalar_t__ KEEP_ALIVE ; 
 scalar_t__ VER_H ; 
 scalar_t__ VER_L ; 
 scalar_t__ VER_LIB_H_ADDR ; 
 scalar_t__ VER_LIB_L_ADDR ; 
 int readl (scalar_t__) ; 
 int readx_poll_timeout (int (*) (scalar_t__),scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int cdn_dp_load_firmware(struct cdn_dp_device *dp, const u32 *i_mem,
			 u32 i_size, const u32 *d_mem, u32 d_size)
{
	u32 reg;
	int i, ret;

	/* reset ucpu before load firmware*/
	writel(APB_IRAM_PATH | APB_DRAM_PATH | APB_XT_RESET,
	       dp->regs + APB_CTRL);

	for (i = 0; i < i_size; i += 4)
		writel(*i_mem++, dp->regs + ADDR_IMEM + i);

	for (i = 0; i < d_size; i += 4)
		writel(*d_mem++, dp->regs + ADDR_DMEM + i);

	/* un-reset ucpu */
	writel(0, dp->regs + APB_CTRL);

	/* check the keep alive register to make sure fw working */
	ret = readx_poll_timeout(readl, dp->regs + KEEP_ALIVE,
				 reg, reg, 2000, FW_ALIVE_TIMEOUT_US);
	if (ret < 0) {
		DRM_DEV_ERROR(dp->dev, "failed to loaded the FW reg = %x\n",
			      reg);
		return -EINVAL;
	}

	reg = readl(dp->regs + VER_L) & 0xff;
	dp->fw_version = reg;
	reg = readl(dp->regs + VER_H) & 0xff;
	dp->fw_version |= reg << 8;
	reg = readl(dp->regs + VER_LIB_L_ADDR) & 0xff;
	dp->fw_version |= reg << 16;
	reg = readl(dp->regs + VER_LIB_H_ADDR) & 0xff;
	dp->fw_version |= reg << 24;

	DRM_DEV_DEBUG(dp->dev, "firmware version: %x\n", dp->fw_version);

	return 0;
}