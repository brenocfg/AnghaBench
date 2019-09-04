#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qlcnic_adapter {TYPE_2__* ahw; } ;
struct TYPE_3__ {int write_statusreg_cmd; int write_enable_bits; } ;
struct TYPE_4__ {TYPE_1__ fdt; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLC_83XX_FLASH_ADDR ; 
 int /*<<< orphan*/  QLC_83XX_FLASH_CONTROL ; 
 int QLC_83XX_FLASH_FDT_WRITE_DEF_SIG ; 
 int QLC_83XX_FLASH_SECOND_ERASE_MS_VAL ; 
 int /*<<< orphan*/  QLC_83XX_FLASH_WRDATA ; 
 int qlcnic_83xx_poll_flash_status_reg (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_wrt_reg_indirect (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 

int qlcnic_83xx_enable_flash_write(struct qlcnic_adapter *adapter)
{
	int ret;
	u32 cmd;
	cmd = adapter->ahw->fdt.write_statusreg_cmd;
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
				     (QLC_83XX_FLASH_FDT_WRITE_DEF_SIG | cmd));
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_WRDATA,
				     adapter->ahw->fdt.write_enable_bits);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_SECOND_ERASE_MS_VAL);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	if (ret)
		return -EIO;

	return 0;
}