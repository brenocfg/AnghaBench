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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int bt_cur_state; int reg_bt_sco; int bt_service; int bt_ant_isolation; int ratio_tx; int ratio_pri; } ;
struct TYPE_3__ {scalar_t__ link_state; } ;
struct rtl_priv {TYPE_2__ btcoexist; TYPE_1__ mac80211; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT_OFFSET_LEN_MASK_32 (int,int) ; 
 int BT_BUSY ; 
 scalar_t__ BT_IDLE ; 
 int BT_MASK ; 
 int BT_OTHERBUSY ; 
 int BT_OTHER_ACTION ; 
 int BT_PAN ; 
 int BT_SCO ; 
 scalar_t__ MAC80211_LINKED ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 
 int rtl_read_dword (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int,int) ; 

__attribute__((used)) static bool rtl92c_bt_state_change(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	u32 polling, ratio_tx, ratio_pri;
	u32 bt_tx, bt_pri;
	u8 bt_state;
	u8 cur_service_type;

	if (rtlpriv->mac80211.link_state < MAC80211_LINKED)
		return false;

	bt_state = rtl_read_byte(rtlpriv, 0x4fd);
	bt_tx = rtl_read_dword(rtlpriv, 0x488) & BT_MASK;
	bt_pri = rtl_read_dword(rtlpriv, 0x48c) & BT_MASK;
	polling = rtl_read_dword(rtlpriv, 0x490);

	if (bt_tx == BT_MASK && bt_pri == BT_MASK &&
	    polling == 0xffffffff && bt_state == 0xff)
		return false;

	bt_state &= BIT_OFFSET_LEN_MASK_32(0, 1);
	if (bt_state != rtlpriv->btcoexist.bt_cur_state) {
		rtlpriv->btcoexist.bt_cur_state = bt_state;

		if (rtlpriv->btcoexist.reg_bt_sco == 3) {
			rtlpriv->btcoexist.bt_service = BT_IDLE;

			bt_state = bt_state |
			  ((rtlpriv->btcoexist.bt_ant_isolation == 1) ?
			  0 : BIT_OFFSET_LEN_MASK_32(1, 1)) |
			  BIT_OFFSET_LEN_MASK_32(2, 1);
			rtl_write_byte(rtlpriv, 0x4fd, bt_state);
		}
		return true;
	}

	ratio_tx = bt_tx * 1000 / polling;
	ratio_pri = bt_pri * 1000 / polling;
	rtlpriv->btcoexist.ratio_tx = ratio_tx;
	rtlpriv->btcoexist.ratio_pri = ratio_pri;

	if (bt_state && rtlpriv->btcoexist.reg_bt_sco == 3) {

		if ((ratio_tx < 30)  && (ratio_pri < 30))
			cur_service_type = BT_IDLE;
		else if ((ratio_pri > 110) && (ratio_pri < 250))
			cur_service_type = BT_SCO;
		else if ((ratio_tx >= 200) && (ratio_pri >= 200))
			cur_service_type = BT_BUSY;
		else if ((ratio_tx >= 350) && (ratio_tx < 500))
			cur_service_type = BT_OTHERBUSY;
		else if (ratio_tx >= 500)
			cur_service_type = BT_PAN;
		else
			cur_service_type = BT_OTHER_ACTION;

		if (cur_service_type != rtlpriv->btcoexist.bt_service) {
			rtlpriv->btcoexist.bt_service = cur_service_type;
			bt_state = bt_state |
			   ((rtlpriv->btcoexist.bt_ant_isolation == 1) ?
			   0 : BIT_OFFSET_LEN_MASK_32(1, 1)) |
			   ((rtlpriv->btcoexist.bt_service != BT_IDLE) ?
			   0 : BIT_OFFSET_LEN_MASK_32(2, 1));

			/* Add interrupt migration when bt is not ini
			 * idle state (no traffic). */
			if (rtlpriv->btcoexist.bt_service != BT_IDLE) {
				rtl_write_word(rtlpriv, 0x504, 0x0ccc);
				rtl_write_byte(rtlpriv, 0x506, 0x54);
				rtl_write_byte(rtlpriv, 0x507, 0x54);
			} else {
				rtl_write_byte(rtlpriv, 0x506, 0x00);
				rtl_write_byte(rtlpriv, 0x507, 0x00);
			}

			rtl_write_byte(rtlpriv, 0x4fd, bt_state);
			return true;
		}
	}

	return false;

}