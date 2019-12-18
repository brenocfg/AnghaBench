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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rtl_phy {int* iqk_bb_backup; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_IQK ; 
 int IQK_DELAY_TIME ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int RFPGA0_XAB_RFINTERFACESW ; 
 int RFPGA0_XB_RFINTERFACEOE ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 _rtl92d_phy_pathb_iqk_5g_normal(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 regeac, regeb4, regebc, regec4, regecc;
	u8 result = 0;
	u8 i;
	u8 retrycount = 2;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path B IQK!\n");
	/* path-A IQK setting */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path-A IQK setting!\n");
	rtl_set_bbreg(hw, 0xe30, MASKDWORD, 0x18008c1f);
	rtl_set_bbreg(hw, 0xe34, MASKDWORD, 0x18008c1f);
	rtl_set_bbreg(hw, 0xe38, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, 0xe3c, MASKDWORD, 0x68110000);

	/* path-B IQK setting */
	rtl_set_bbreg(hw, 0xe50, MASKDWORD, 0x18008c2f);
	rtl_set_bbreg(hw, 0xe54, MASKDWORD, 0x18008c2f);
	rtl_set_bbreg(hw, 0xe58, MASKDWORD, 0x82140307);
	rtl_set_bbreg(hw, 0xe5c, MASKDWORD, 0x68160960);

	/* LO calibration setting */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "LO calibration setting!\n");
	rtl_set_bbreg(hw, 0xe4c, MASKDWORD, 0x00462911);

	/* path-B PA on */
	rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW, MASKDWORD, 0x0f600700);
	rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE, MASKDWORD, 0x061f0d30);

	for (i = 0; i < retrycount; i++) {
		/* One shot, path B LOK & IQK */
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"One shot, path A LOK & IQK!\n");
		rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xfa000000);
		rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xf8000000);

		/* delay x ms */
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"Delay %d ms for One shot, path B LOK & IQK.\n", 10);
		mdelay(IQK_DELAY_TIME * 10);

		/* Check failed */
		regeac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xeac = 0x%x\n", regeac);
		regeb4 = rtl_get_bbreg(hw, 0xeb4, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xeb4 = 0x%x\n", regeb4);
		regebc = rtl_get_bbreg(hw, 0xebc, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xebc = 0x%x\n", regebc);
		regec4 = rtl_get_bbreg(hw, 0xec4, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xec4 = 0x%x\n", regec4);
		regecc = rtl_get_bbreg(hw, 0xecc, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xecc = 0x%x\n", regecc);
		if (!(regeac & BIT(31)) &&
		    (((regeb4 & 0x03FF0000) >> 16) != 0x142))
			result |= 0x01;
		else
			continue;
		if (!(regeac & BIT(30)) &&
		    (((regec4 & 0x03FF0000) >> 16) != 0x132)) {
			result |= 0x02;
			break;
		} else {
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"Path B Rx IQK fail!!\n");
		}
	}

	/* path B PA off */
	rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW, MASKDWORD,
		      rtlphy->iqk_bb_backup[0]);
	rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE, MASKDWORD,
		      rtlphy->iqk_bb_backup[2]);
	return result;
}