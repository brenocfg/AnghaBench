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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_hardware_context {int* extra_capability; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CMD_82XX_SET_DRV_VER ; 
 int /*<<< orphan*/  QLCNIC_CMD_83XX_SET_DRV_VER ; 
 int QLCNIC_FW_CAPABILITY_SET_DRV_VER ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_fw_cmd_set_drv_version (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

void qlcnic_set_drv_version(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	u32 fw_cmd = 0;

	if (qlcnic_82xx_check(adapter))
		fw_cmd = QLCNIC_CMD_82XX_SET_DRV_VER;
	else if (qlcnic_83xx_check(adapter))
		fw_cmd = QLCNIC_CMD_83XX_SET_DRV_VER;

	if (ahw->extra_capability[0] & QLCNIC_FW_CAPABILITY_SET_DRV_VER)
		qlcnic_fw_cmd_set_drv_version(adapter, fw_cmd);
}