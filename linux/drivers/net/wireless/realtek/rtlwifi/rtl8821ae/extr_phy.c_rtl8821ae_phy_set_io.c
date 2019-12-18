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
struct TYPE_3__ {int /*<<< orphan*/  opmode; } ;
struct TYPE_4__ {int xaagccore1; int cca; } ;
struct rtl_phy {int current_io_type; int set_io_inprogress; TYPE_2__ initgain_backup; } ;
struct dig_t {int cur_igvalue; int cur_cck_cca_thres; } ;
struct rtl_priv {TYPE_1__ mac80211; struct rtl_phy phy; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
#define  IO_CMD_PAUSE_BAND0_DM_BY_SCAN 130 
#define  IO_CMD_PAUSE_BAND1_DM_BY_SCAN 129 
#define  IO_CMD_RESUME_DM_BY_SCAN 128 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  _rtl8821ae_resume_tx_beacon (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8821ae_stop_tx_beacon (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rtl8821ae_dm_write_cck_cca_thres (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8821ae_dm_write_dig (struct ieee80211_hw*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8821ae_phy_set_io(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	RT_TRACE(rtlpriv, COMP_CMD, DBG_TRACE,
		 "--->Cmd(%#x), set_io_inprogress(%d)\n",
		  rtlphy->current_io_type, rtlphy->set_io_inprogress);
	switch (rtlphy->current_io_type) {
	case IO_CMD_RESUME_DM_BY_SCAN:
		if (rtlpriv->mac80211.opmode == NL80211_IFTYPE_ADHOC)
			_rtl8821ae_resume_tx_beacon(hw);
		rtl8821ae_dm_write_dig(hw, rtlphy->initgain_backup.xaagccore1);
		rtl8821ae_dm_write_cck_cca_thres(hw,
						 rtlphy->initgain_backup.cca);
		break;
	case IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
		if (rtlpriv->mac80211.opmode == NL80211_IFTYPE_ADHOC)
			_rtl8821ae_stop_tx_beacon(hw);
		rtlphy->initgain_backup.xaagccore1 = dm_digtable->cur_igvalue;
		rtl8821ae_dm_write_dig(hw, 0x17);
		rtlphy->initgain_backup.cca = dm_digtable->cur_cck_cca_thres;
		rtl8821ae_dm_write_cck_cca_thres(hw, 0x40);
		break;
	case IO_CMD_PAUSE_BAND1_DM_BY_SCAN:
		break;
	default:
		pr_err("switch case %#x not processed\n",
		       rtlphy->current_io_type);
		break;
	}
	rtlphy->set_io_inprogress = false;
	RT_TRACE(rtlpriv, COMP_CMD, DBG_TRACE,
		 "(%#x)\n", rtlphy->current_io_type);
}