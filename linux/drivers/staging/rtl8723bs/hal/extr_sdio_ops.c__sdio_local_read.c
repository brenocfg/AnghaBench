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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct intf_hdl {int dummy; } ;
struct TYPE_2__ {struct intf_hdl intf; } ;
struct adapter {TYPE_1__ iopriv; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_APFM_ON_MAC ; 
 int /*<<< orphan*/  HalSdioGetCmdAddr8723BSdio (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RND4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDIO_LOCAL_DEVICE_ID ; 
 int _sd_cmd52_read (struct intf_hdl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _sd_read (struct intf_hdl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtw_malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 _sdio_local_read(
	struct adapter *adapter,
	u32 addr,
	u32 cnt,
	u8 *buf
)
{
	struct intf_hdl *intfhdl;
	u8 mac_pwr_ctrl_on;
	s32 err;
	u8 *tmpbuf;
	u32 n;


	intfhdl = &adapter->iopriv.intf;

	HalSdioGetCmdAddr8723BSdio(adapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);

	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	if (!mac_pwr_ctrl_on)
		return _sd_cmd52_read(intfhdl, addr, cnt, buf);

	n = RND4(cnt);
	tmpbuf = rtw_malloc(n);
	if (!tmpbuf)
		return -1;

	err = _sd_read(intfhdl, addr, n, tmpbuf);
	if (!err)
		memcpy(buf, tmpbuf, cnt);

	kfree(tmpbuf);

	return err;
}