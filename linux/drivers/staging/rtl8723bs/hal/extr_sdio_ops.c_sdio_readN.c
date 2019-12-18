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
typedef  int s32 ;
struct TYPE_2__ {scalar_t__ bFwCurrentInPSMode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_APFM_ON_MAC ; 
 scalar_t__ WLAN_IOREG_DEVICE_ID ; 
 int _cvrt2ftaddr (int,scalar_t__*,int*) ; 
 TYPE_1__* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__* rtw_malloc (int) ; 
 int sd_cmd52_read (struct intf_hdl*,int,int,scalar_t__*) ; 
 int sd_read (struct intf_hdl*,int,int,scalar_t__*) ; 

__attribute__((used)) static s32 sdio_readN(struct intf_hdl *intfhdl, u32 addr, u32 cnt, u8 *buf)
{
	struct adapter *adapter;
	u8 mac_pwr_ctrl_on;
	u8 device_id;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	s32 err;

	adapter = intfhdl->padapter;
	err = 0;

	ftaddr = _cvrt2ftaddr(addr, &device_id, &offset);

	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	if (
		((device_id == WLAN_IOREG_DEVICE_ID) && (offset < 0x100)) ||
		(!mac_pwr_ctrl_on) ||
		(adapter_to_pwrctl(adapter)->bFwCurrentInPSMode)
	)
		return sd_cmd52_read(intfhdl, ftaddr, cnt, buf);

	/*  4 bytes alignment */
	shift = ftaddr & 0x3;
	if (shift == 0) {
		err = sd_read(intfhdl, ftaddr, cnt, buf);
	} else {
		u8 *tmpbuf;
		u32 n;

		ftaddr &= ~(u16)0x3;
		n = cnt + shift;
		tmpbuf = rtw_malloc(n);
		if (!tmpbuf)
			return -1;

		err = sd_read(intfhdl, ftaddr, n, tmpbuf);
		if (!err)
			memcpy(buf, tmpbuf + shift, cnt);
		kfree(tmpbuf);
	}
	return err;
}