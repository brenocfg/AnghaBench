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
typedef  void* u8 ;
struct rtl_phy {void* framesync; scalar_t__ framesync_c34; void** default_initialgain; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  MASKBYTE0 ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  ROFDM0_RXDETECTOR2 ; 
 int /*<<< orphan*/  ROFDM0_RXDETECTOR3 ; 
 int /*<<< orphan*/  ROFDM0_XAAGCCORE1 ; 
 int /*<<< orphan*/  ROFDM0_XBAGCCORE1 ; 
 int /*<<< orphan*/  ROFDM0_XCAGCCORE1 ; 
 int /*<<< orphan*/  ROFDM0_XDAGCCORE1 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,...) ; 
 scalar_t__ rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92c_phy_get_hw_reg_originalvalue(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);

	rtlphy->default_initialgain[0] =
	    (u8)rtl_get_bbreg(hw, ROFDM0_XAAGCCORE1, MASKBYTE0);
	rtlphy->default_initialgain[1] =
	    (u8)rtl_get_bbreg(hw, ROFDM0_XBAGCCORE1, MASKBYTE0);
	rtlphy->default_initialgain[2] =
	    (u8)rtl_get_bbreg(hw, ROFDM0_XCAGCCORE1, MASKBYTE0);
	rtlphy->default_initialgain[3] =
	    (u8)rtl_get_bbreg(hw, ROFDM0_XDAGCCORE1, MASKBYTE0);

	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
		 "Default initial gain (c50=0x%x, c58=0x%x, c60=0x%x, c68=0x%x\n",
		  rtlphy->default_initialgain[0],
		  rtlphy->default_initialgain[1],
		  rtlphy->default_initialgain[2],
		  rtlphy->default_initialgain[3]);

	rtlphy->framesync = (u8)rtl_get_bbreg(hw,
					       ROFDM0_RXDETECTOR3, MASKBYTE0);
	rtlphy->framesync_c34 = rtl_get_bbreg(hw,
					      ROFDM0_RXDETECTOR2, MASKDWORD);

	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
		 "Default framesync (0x%x) = 0x%x\n",
		  ROFDM0_RXDETECTOR3, rtlphy->framesync);
}