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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ macphymode; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int REG_PBP ; 
 scalar_t__ REG_RQPN ; 
 int REG_RQPN_NPQ ; 
 int REG_RX_DRVINFO_SZ ; 
 int REG_TDECTRL ; 
 scalar_t__ REG_TRXFF_BNDY ; 
 int REG_TXPKTBUF_BCNQ_BDNY ; 
 int REG_TXPKTBUF_MGQ_BDNY ; 
 scalar_t__ SINGLEMAC_SINGLEPHY ; 
 int _rtl92de_llt_write (struct ieee80211_hw*,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_word (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,scalar_t__,int) ; 

__attribute__((used)) static bool _rtl92de_llt_table_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	unsigned short i;
	u8 txpktbuf_bndy;
	u8 maxpage;
	bool status;
	u32 value32; /* High+low page number */
	u8 value8;	 /* normal page number */

	if (rtlpriv->rtlhal.macphymode == SINGLEMAC_SINGLEPHY) {
		maxpage = 255;
		txpktbuf_bndy = 246;
		value8 = 0;
		value32 = 0x80bf0d29;
	} else {
		maxpage = 127;
		txpktbuf_bndy = 123;
		value8 = 0;
		value32 = 0x80750005;
	}

	/* Set reserved page for each queue */
	/* 11.  RQPN 0x200[31:0] = 0x80BD1C1C */
	/* load RQPN */
	rtl_write_byte(rtlpriv, REG_RQPN_NPQ, value8);
	rtl_write_dword(rtlpriv, REG_RQPN, value32);

	/* 12.  TXRKTBUG_PG_BNDY 0x114[31:0] = 0x27FF00F6 */
	/* TXRKTBUG_PG_BNDY */
	rtl_write_dword(rtlpriv, REG_TRXFF_BNDY,
			(rtl_read_word(rtlpriv, REG_TRXFF_BNDY + 2) << 16 |
			txpktbuf_bndy));

	/* 13.  TDECTRL[15:8] 0x209[7:0] = 0xF6 */
	/* Beacon Head for TXDMA */
	rtl_write_byte(rtlpriv, REG_TDECTRL + 1, txpktbuf_bndy);

	/* 14.  BCNQ_PGBNDY 0x424[7:0] =  0xF6 */
	/* BCNQ_PGBNDY */
	rtl_write_byte(rtlpriv, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	rtl_write_byte(rtlpriv, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);

	/* 15.  WMAC_LBK_BF_HD 0x45D[7:0] =  0xF6 */
	/* WMAC_LBK_BF_HD */
	rtl_write_byte(rtlpriv, 0x45D, txpktbuf_bndy);

	/* Set Tx/Rx page size (Tx must be 128 Bytes, */
	/* Rx can be 64,128,256,512,1024 bytes) */
	/* 16.  PBP [7:0] = 0x11 */
	/* TRX page size */
	rtl_write_byte(rtlpriv, REG_PBP, 0x11);

	/* 17.  DRV_INFO_SZ = 0x04 */
	rtl_write_byte(rtlpriv, REG_RX_DRVINFO_SZ, 0x4);

	/* 18.  LLT_table_init(Adapter);  */
	for (i = 0; i < (txpktbuf_bndy - 1); i++) {
		status = _rtl92de_llt_write(hw, i, i + 1);
		if (true != status)
			return status;
	}

	/* end of list */
	status = _rtl92de_llt_write(hw, (txpktbuf_bndy - 1), 0xFF);
	if (true != status)
		return status;

	/* Make the other pages as ring buffer */
	/* This ring buffer is used as beacon buffer if we */
	/* config this MAC as two MAC transfer. */
	/* Otherwise used as local loopback buffer.  */
	for (i = txpktbuf_bndy; i < maxpage; i++) {
		status = _rtl92de_llt_write(hw, i, (i + 1));
		if (true != status)
			return status;
	}

	/* Let last entry point to the start entry of ring buffer */
	status = _rtl92de_llt_write(hw, maxpage, txpktbuf_bndy);
	if (true != status)
		return status;

	return true;
}