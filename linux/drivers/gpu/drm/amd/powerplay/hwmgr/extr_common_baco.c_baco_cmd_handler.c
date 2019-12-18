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
struct pp_hwmgr {scalar_t__ adev; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CMD_DELAY_MS 132 
#define  CMD_DELAY_US 131 
#define  CMD_READMODIFYWRITE 130 
#define  CMD_WAITFOR 129 
#define  CMD_WRITE 128 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int baco_wait_register (struct pp_hwmgr*,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool baco_cmd_handler(struct pp_hwmgr *hwmgr, u32 command, u32 reg, u32 mask,
			        u32 shift, u32 value, u32 timeout)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)(hwmgr->adev);
	u32 data;
	bool ret = true;

	switch (command) {
	case CMD_WRITE:
		WREG32(reg, value << shift);
		break;
	case CMD_READMODIFYWRITE:
		data = RREG32(reg);
		data = (data & (~mask)) | (value << shift);
		WREG32(reg, data);
		break;
	case CMD_WAITFOR:
		ret = baco_wait_register(hwmgr, reg, mask, value);
		break;
	case CMD_DELAY_MS:
		if (timeout)
			/* Delay in milli Seconds */
			msleep(timeout);
		break;
	case CMD_DELAY_US:
		if (timeout)
			/* Delay in micro Seconds */
			udelay(timeout);
		break;

	default:
		dev_warn(adev->dev, "Invalid BACO command.\n");
		ret = false;
	}

	return ret;
}