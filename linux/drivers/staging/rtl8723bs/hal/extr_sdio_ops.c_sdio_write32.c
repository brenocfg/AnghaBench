#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct intf_hdl {struct adapter* padapter; } ;
struct adapter {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ __le32 ;
struct TYPE_2__ {scalar_t__ bFwCurrentInPSMode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_APFM_ON_MAC ; 
 scalar_t__ WLAN_IOREG_DEVICE_ID ; 
 int _cvrt2ftaddr (int,scalar_t__*,int*) ; 
 TYPE_1__* adapter_to_pwrctl (struct adapter*) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ sd_cmd52_write (struct intf_hdl*,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  sd_write32 (struct intf_hdl*,int,int,scalar_t__*) ; 

__attribute__((used)) static s32 sdio_write32(struct intf_hdl *intfhdl, u32 addr, u32 val)
{
	struct adapter *adapter;
	u8 mac_pwr_ctrl_on;
	u8 device_id;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	s32 err;
	__le32 le_tmp;

	adapter = intfhdl->padapter;
	err = 0;

	ftaddr = _cvrt2ftaddr(addr, &device_id, &offset);

	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	if (
		((device_id == WLAN_IOREG_DEVICE_ID) && (offset < 0x100)) ||
		(!mac_pwr_ctrl_on) ||
		(adapter_to_pwrctl(adapter)->bFwCurrentInPSMode)
	) {
		le_tmp = cpu_to_le32(val);

		return sd_cmd52_write(intfhdl, ftaddr, 4, (u8 *)&le_tmp);
	}

	/*  4 bytes alignment */
	shift = ftaddr & 0x3;
	if (shift == 0) {
		sd_write32(intfhdl, ftaddr, val, &err);
	} else {
		le_tmp = cpu_to_le32(val);
		err = sd_cmd52_write(intfhdl, ftaddr, 4, (u8 *)&le_tmp);
	}
	return err;
}