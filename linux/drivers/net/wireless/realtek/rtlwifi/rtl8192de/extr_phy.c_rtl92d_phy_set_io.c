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
struct TYPE_2__ {int xaagccore1; } ;
struct rtl_phy {int current_io_type; int set_io_inprogress; TYPE_1__ initgain_backup; int /*<<< orphan*/  current_channel; } ;
struct dig_t {int cur_igvalue; } ;
struct rtl_priv {struct rtl_phy phy; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
#define  IO_CMD_PAUSE_DM_BY_SCAN 129 
#define  IO_CMD_RESUME_DM_BY_SCAN 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rtl92d_dm_write_dig (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_phy_set_txpower_level (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92d_phy_set_io(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *de_digtable = &rtlpriv->dm_digtable;
	struct rtl_phy *rtlphy = &(rtlpriv->phy);

	RT_TRACE(rtlpriv, COMP_CMD, DBG_TRACE,
		 "--->Cmd(%#x), set_io_inprogress(%d)\n",
		 rtlphy->current_io_type, rtlphy->set_io_inprogress);
	switch (rtlphy->current_io_type) {
	case IO_CMD_RESUME_DM_BY_SCAN:
		de_digtable->cur_igvalue = rtlphy->initgain_backup.xaagccore1;
		rtl92d_dm_write_dig(hw);
		rtl92d_phy_set_txpower_level(hw, rtlphy->current_channel);
		break;
	case IO_CMD_PAUSE_DM_BY_SCAN:
		rtlphy->initgain_backup.xaagccore1 = de_digtable->cur_igvalue;
		de_digtable->cur_igvalue = 0x37;
		rtl92d_dm_write_dig(hw);
		break;
	default:
		pr_err("switch case %#x not processed\n",
		       rtlphy->current_io_type);
		break;
	}
	rtlphy->set_io_inprogress = false;
	RT_TRACE(rtlpriv, COMP_CMD, DBG_TRACE, "<---(%#x)\n",
		 rtlphy->current_io_type);
}