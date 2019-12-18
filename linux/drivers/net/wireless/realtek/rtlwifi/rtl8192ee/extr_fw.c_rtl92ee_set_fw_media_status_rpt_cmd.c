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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_92E_MSRRPT ; 
 int /*<<< orphan*/  SET_H2CCMD_MSRRPT_PARM_MACID_IND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_MSRRPT_PARM_OPMODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92ee_fill_h2c_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void rtl92ee_set_fw_media_status_rpt_cmd(struct ieee80211_hw *hw, u8 mstatus)
{
	u8 parm[3] = { 0 , 0 , 0 };
	/* parm[0]: bit0=0-->Disconnect, bit0=1-->Connect
	 *          bit1=0-->update Media Status to MACID
	 *          bit1=1-->update Media Status from MACID to MACID_End
	 * parm[1]: MACID, if this is INFRA_STA, MacID = 0
	 * parm[2]: MACID_End
	 */

	SET_H2CCMD_MSRRPT_PARM_OPMODE(parm, mstatus);
	SET_H2CCMD_MSRRPT_PARM_MACID_IND(parm, 0);

	rtl92ee_fill_h2c_cmd(hw, H2C_92E_MSRRPT, 3, parm);
}