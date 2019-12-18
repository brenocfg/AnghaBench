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
struct TYPE_2__ {scalar_t__ fw_rssi; } ;
struct _adapter {TYPE_1__ recvpriv; int /*<<< orphan*/  mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCMD_CTRL_REG ; 
 int /*<<< orphan*/  IOCMD_DATA_REG ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int r8712_read32 (struct _adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ r8712_signal_scale_mapping (int) ; 
 int /*<<< orphan*/  r8712_write32 (struct _adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void query_fw_rx_phy_status(struct _adapter *padapter)
{
	u32 val32 = 0;
	int pollingcnts = 50;

	if (check_fwstate(&padapter->mlmepriv, _FW_LINKED)) {
		r8712_write32(padapter, IOCMD_CTRL_REG, 0xf4000001);
		msleep(100);
		/* Wait FW complete IO Cmd */
		while ((r8712_read32(padapter, IOCMD_CTRL_REG)) &&
		       (pollingcnts > 0)) {
			pollingcnts--;
			msleep(20);
		}
		if (pollingcnts != 0)
			val32 = r8712_read32(padapter, IOCMD_DATA_REG);
		else /* time out */
			val32 = 0;
		val32 >>= 4;
		padapter->recvpriv.fw_rssi =
			 (u8)r8712_signal_scale_mapping(val32);
	}
}