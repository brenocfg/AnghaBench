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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int COMP_INIT ; 
 int COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int,int /*<<< orphan*/ ,char*,...) ; 
 int _rtl8821ae_dbi_read (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  _rtl8821ae_dbi_write (struct rtl_priv*,int,int) ; 
 int _rtl8821ae_mdio_read (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  _rtl8821ae_mdio_write (struct rtl_priv*,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8821ae_enable_l1off(struct ieee80211_hw *hw)
{
	u8 tmp  = 0;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "--->\n");

	tmp = _rtl8821ae_dbi_read(rtlpriv, 0x160);
	if (!(tmp & (BIT(2) | BIT(3)))) {
		RT_TRACE(rtlpriv, COMP_POWER | COMP_INIT, DBG_LOUD,
			 "0x160(%#x)return!!\n", tmp);
		return;
	}

	tmp = _rtl8821ae_mdio_read(rtlpriv, 0x1b);
	_rtl8821ae_mdio_write(rtlpriv, 0x1b, (tmp | BIT(4)));

	tmp = _rtl8821ae_dbi_read(rtlpriv, 0x718);
	_rtl8821ae_dbi_write(rtlpriv, 0x718, tmp | BIT(5));

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "<---\n");
}