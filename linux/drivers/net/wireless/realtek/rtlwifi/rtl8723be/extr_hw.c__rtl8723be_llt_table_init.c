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
 int REG_PBP ; 
 int /*<<< orphan*/  REG_RQPN ; 
 int REG_RQPN_NPQ ; 
 int REG_RX_DRVINFO_SZ ; 
 int REG_TDECTRL ; 
 int /*<<< orphan*/  REG_TRXFF_BNDY ; 
 int REG_TXPKTBUF_BCNQ_BDNY ; 
 int REG_TXPKTBUF_MGQ_BDNY ; 
 int _rtl8723be_llt_write (struct ieee80211_hw*,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool _rtl8723be_llt_table_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	unsigned short i;
	u8 txpktbuf_bndy;
	u8 maxpage;
	bool status;

	maxpage = 255;
	txpktbuf_bndy = 245;

	rtl_write_dword(rtlpriv, REG_TRXFF_BNDY,
			(0x27FF0000 | txpktbuf_bndy));
	rtl_write_byte(rtlpriv, REG_TDECTRL + 1, txpktbuf_bndy);

	rtl_write_byte(rtlpriv, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	rtl_write_byte(rtlpriv, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);

	rtl_write_byte(rtlpriv, 0x45D, txpktbuf_bndy);
	rtl_write_byte(rtlpriv, REG_PBP, 0x31);
	rtl_write_byte(rtlpriv, REG_RX_DRVINFO_SZ, 0x4);

	for (i = 0; i < (txpktbuf_bndy - 1); i++) {
		status = _rtl8723be_llt_write(hw, i, i + 1);
		if (!status)
			return status;
	}

	status = _rtl8723be_llt_write(hw, (txpktbuf_bndy - 1), 0xFF);

	if (!status)
		return status;

	for (i = txpktbuf_bndy; i < maxpage; i++) {
		status = _rtl8723be_llt_write(hw, i, (i + 1));
		if (!status)
			return status;
	}

	status = _rtl8723be_llt_write(hw, maxpage, txpktbuf_bndy);
	if (!status)
		return status;

	rtl_write_dword(rtlpriv, REG_RQPN, 0x80e40808);
	rtl_write_byte(rtlpriv, REG_RQPN_NPQ, 0x00);

	return true;
}