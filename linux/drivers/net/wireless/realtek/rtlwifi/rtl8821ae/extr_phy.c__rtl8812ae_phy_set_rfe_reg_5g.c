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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  bt_coexistence; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct rtl_hal {int rfe_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BMASKDWORD ; 
 int BMASKRFEINV ; 
 int RA_RFE_INV ; 
 int RA_RFE_PINMUX ; 
 int RB_RFE_INV ; 
 int RB_RFE_PINMUX ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl8812ae_phy_set_rfe_reg_5g(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 tmp;

	switch (rtlhal->rfe_type) {
	case 0:
		rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD, 0x77337717);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x77337717);
		rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x010);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x010);
		break;
	case 1:
		if (rtlpriv->btcoexist.bt_coexistence) {
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xffffff, 0x337717);
			rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD,
				      0x77337717);
			rtl_set_bbreg(hw, RA_RFE_INV, 0x33f00000, 0x000);
			rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x000);
		} else {
			rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD,
				      0x77337717);
			rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD,
				      0x77337717);
			rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x000);
			rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x000);
		}
		break;
	case 3:
		rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD, 0x54337717);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x54337717);
		rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x010);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x010);
		rtl_set_bbreg(hw, 0x900, 0x00000303, 0x1);
		break;
	case 5:
		rtl_write_byte(rtlpriv, RA_RFE_PINMUX + 2, 0x33);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x77337777);
		tmp = rtl_read_byte(rtlpriv, RA_RFE_INV + 3);
		rtl_write_byte(rtlpriv, RA_RFE_INV + 3, tmp | 0x1);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x010);
		break;
	case 2:
	case 4:
	default:
		rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD, 0x77337777);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x77337777);
		rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x010);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x010);
		break;
	}
}