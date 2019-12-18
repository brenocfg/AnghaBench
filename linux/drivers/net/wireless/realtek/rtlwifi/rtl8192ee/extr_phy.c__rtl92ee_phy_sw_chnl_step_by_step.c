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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct swchnlcmd {int cmdid; int para2; scalar_t__ msdelay; int /*<<< orphan*/  para1; } ;
struct rtl_phy {int num_total_rfpath; int* rfreg_chnlval; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int CMDID_END ; 
#define  CMDID_RF_WRITEREG 132 
#define  CMDID_SET_TXPOWEROWER_LEVEL 131 
#define  CMDID_WRITEPORT_UCHAR 130 
#define  CMDID_WRITEPORT_ULONG 129 
#define  CMDID_WRITEPORT_USHORT 128 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int MAX_POSTCMD_CNT ; 
 int MAX_PRECMD_CNT ; 
 int MAX_RFDEPENDCMD_CNT ; 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  _rtl92ee_phy_set_sw_chnl_cmdarray (struct swchnlcmd*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rtl92ee_phy_set_txpower_level (struct ieee80211_hw*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool _rtl92ee_phy_sw_chnl_step_by_step(struct ieee80211_hw *hw,
					      u8 channel, u8 *stage, u8 *step,
					      u32 *delay)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct swchnlcmd precommoncmd[MAX_PRECMD_CNT];
	u32 precommoncmdcnt;
	struct swchnlcmd postcommoncmd[MAX_POSTCMD_CNT];
	u32 postcommoncmdcnt;
	struct swchnlcmd rfdependcmd[MAX_RFDEPENDCMD_CNT];
	u32 rfdependcmdcnt;
	struct swchnlcmd *currentcmd = NULL;
	u8 rfpath;
	u8 num_total_rfpath = rtlphy->num_total_rfpath;

	precommoncmdcnt = 0;
	_rtl92ee_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
					  MAX_PRECMD_CNT,
					  CMDID_SET_TXPOWEROWER_LEVEL, 0, 0, 0);
	_rtl92ee_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
					  MAX_PRECMD_CNT, CMDID_END, 0, 0, 0);

	postcommoncmdcnt = 0;

	_rtl92ee_phy_set_sw_chnl_cmdarray(postcommoncmd, postcommoncmdcnt++,
					  MAX_POSTCMD_CNT, CMDID_END, 0, 0, 0);

	rfdependcmdcnt = 0;

	WARN_ONCE((channel < 1 || channel > 14),
		  "rtl8192ee: illegal channel for Zebra: %d\n", channel);

	_rtl92ee_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
					  MAX_RFDEPENDCMD_CNT,
					  CMDID_RF_WRITEREG,
					  RF_CHNLBW, channel, 10);

	_rtl92ee_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
					  MAX_RFDEPENDCMD_CNT, CMDID_END,
					  0, 0, 0);

	do {
		switch (*stage) {
		case 0:
			currentcmd = &precommoncmd[*step];
			break;
		case 1:
			currentcmd = &rfdependcmd[*step];
			break;
		case 2:
			currentcmd = &postcommoncmd[*step];
			break;
		default:
			pr_err("Invalid 'stage' = %d, Check it!\n",
			       *stage);
			return true;
		}

		if (currentcmd->cmdid == CMDID_END) {
			if ((*stage) == 2)
				return true;
			(*stage)++;
			(*step) = 0;
			continue;
		}

		switch (currentcmd->cmdid) {
		case CMDID_SET_TXPOWEROWER_LEVEL:
			rtl92ee_phy_set_txpower_level(hw, channel);
			break;
		case CMDID_WRITEPORT_ULONG:
			rtl_write_dword(rtlpriv, currentcmd->para1,
					currentcmd->para2);
			break;
		case CMDID_WRITEPORT_USHORT:
			rtl_write_word(rtlpriv, currentcmd->para1,
				       (u16)currentcmd->para2);
			break;
		case CMDID_WRITEPORT_UCHAR:
			rtl_write_byte(rtlpriv, currentcmd->para1,
				       (u8)currentcmd->para2);
			break;
		case CMDID_RF_WRITEREG:
			for (rfpath = 0; rfpath < num_total_rfpath; rfpath++) {
				rtlphy->rfreg_chnlval[rfpath] =
					((rtlphy->rfreg_chnlval[rfpath] &
					  0xfffff00) | currentcmd->para2);

				rtl_set_rfreg(hw, (enum radio_path)rfpath,
					      currentcmd->para1,
					      0x3ff,
					      rtlphy->rfreg_chnlval[rfpath]);
			}
			break;
		default:
			RT_TRACE(rtlpriv, COMP_ERR, DBG_LOUD,
				 "switch case %#x not processed\n",
				 currentcmd->cmdid);
			break;
		}

		break;
	} while (true);

	(*delay) = currentcmd->msdelay;
	(*step)++;
	return false;
}