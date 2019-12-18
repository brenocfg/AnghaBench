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
struct rtl_hal {int pa_type_2g; int type_gpa; int pa_type_5g; int type_apa; int lna_type_2g; int type_glna; int lna_type_5g; int type_alna; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  _rtl8812ae_read_pa_type (struct ieee80211_hw*,int*,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8812ae_read_amplifier_type(struct ieee80211_hw *hw, u8 *hwinfo,
					   bool autoload_fail)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);

	u8 ext_type_pa_2g_a  = (hwinfo[0XBD] & BIT(2))      >> 2; /* 0XBD[2] */
	u8 ext_type_pa_2g_b  = (hwinfo[0XBD] & BIT(6))      >> 6; /* 0XBD[6] */
	u8 ext_type_pa_5g_a  = (hwinfo[0XBF] & BIT(2))      >> 2; /* 0XBF[2] */
	u8 ext_type_pa_5g_b  = (hwinfo[0XBF] & BIT(6))      >> 6; /* 0XBF[6] */
	/* 0XBD[1:0] */
	u8 ext_type_lna_2g_a = (hwinfo[0XBD] & (BIT(1) | BIT(0))) >> 0;
	/* 0XBD[5:4] */
	u8 ext_type_lna_2g_b = (hwinfo[0XBD] & (BIT(5) | BIT(4))) >> 4;
	/* 0XBF[1:0] */
	u8 ext_type_lna_5g_a = (hwinfo[0XBF] & (BIT(1) | BIT(0))) >> 0;
	/* 0XBF[5:4] */
	u8 ext_type_lna_5g_b = (hwinfo[0XBF] & (BIT(5) | BIT(4))) >> 4;

	_rtl8812ae_read_pa_type(hw, hwinfo, autoload_fail);

	/* [2.4G] Path A and B are both extPA */
	if ((rtlhal->pa_type_2g & (BIT(5) | BIT(4))) == (BIT(5) | BIT(4)))
		rtlhal->type_gpa  = ext_type_pa_2g_b  << 2 | ext_type_pa_2g_a;

	/* [5G] Path A and B are both extPA */
	if ((rtlhal->pa_type_5g & (BIT(1) | BIT(0))) == (BIT(1) | BIT(0)))
		rtlhal->type_apa  = ext_type_pa_5g_b  << 2 | ext_type_pa_5g_a;

	/* [2.4G] Path A and B are both extLNA */
	if ((rtlhal->lna_type_2g & (BIT(7) | BIT(3))) == (BIT(7) | BIT(3)))
		rtlhal->type_glna = ext_type_lna_2g_b << 2 | ext_type_lna_2g_a;

	/* [5G] Path A and B are both extLNA */
	if ((rtlhal->lna_type_5g & (BIT(7) | BIT(3))) == (BIT(7) | BIT(3)))
		rtlhal->type_alna = ext_type_lna_5g_b << 2 | ext_type_lna_5g_a;
}