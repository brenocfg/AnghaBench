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
typedef  int u32 ;
typedef  int u16 ;
struct mlme_priv {int dummy; } ;
struct eeprom_priv {scalar_t__ CustomerID; } ;
struct adapter {scalar_t__ in_cta_test; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int DIS_TSF_UDT ; 
 struct eeprom_priv* GET_EEPROM_EFUSE_PRIV (struct adapter*) ; 
 int RCR_CBSSID_BCN ; 
 int RCR_CBSSID_DATA ; 
 int /*<<< orphan*/  REG_BCN_CTRL ; 
 int /*<<< orphan*/  REG_RCR ; 
 int /*<<< orphan*/  REG_RL ; 
 int /*<<< orphan*/  REG_RXFLTMAP2 ; 
 int RETRY_LIMIT_LONG_SHIFT ; 
 int RETRY_LIMIT_SHORT_SHIFT ; 
 scalar_t__ RT_CID_CCX ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_STATION_STATE ; 
 int check_fwstate (struct mlme_priv*,int) ; 
 int rtw_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int rtw_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write16 (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hw_var_set_mlme_join(struct adapter *padapter, u8 variable, u8 *val)
{
	u8 val8;
	u16 val16;
	u32 val32;
	u8 RetryLimit;
	u8 type;
	struct mlme_priv *pmlmepriv;
	struct eeprom_priv *pEEPROM;


	RetryLimit = 0x30;
	type = *(u8 *)val;
	pmlmepriv = &padapter->mlmepriv;
	pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	if (type == 0) { /*  prepare to join */
		/* enable to rx data frame.Accept all data frame */
		/* rtw_write32(padapter, REG_RCR, rtw_read32(padapter, REG_RCR)|RCR_ADF); */
		rtw_write16(padapter, REG_RXFLTMAP2, 0xFFFF);

		val32 = rtw_read32(padapter, REG_RCR);
		if (padapter->in_cta_test)
			val32 &= ~(RCR_CBSSID_DATA | RCR_CBSSID_BCN);/*  RCR_ADF */
		else
			val32 |= RCR_CBSSID_DATA|RCR_CBSSID_BCN;
		rtw_write32(padapter, REG_RCR, val32);

		if (check_fwstate(pmlmepriv, WIFI_STATION_STATE) == true)
			RetryLimit = (pEEPROM->CustomerID == RT_CID_CCX) ? 7 : 48;
		else /*  Ad-hoc Mode */
			RetryLimit = 0x7;
	} else if (type == 1) /* joinbss_event call back when join res < 0 */
		rtw_write16(padapter, REG_RXFLTMAP2, 0x00);
	else if (type == 2) { /* sta add event call back */
		/* enable update TSF */
		val8 = rtw_read8(padapter, REG_BCN_CTRL);
		val8 &= ~DIS_TSF_UDT;
		rtw_write8(padapter, REG_BCN_CTRL, val8);

		if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE))
			RetryLimit = 0x7;
	}

	val16 = (RetryLimit << RETRY_LIMIT_SHORT_SHIFT) | (RetryLimit << RETRY_LIMIT_LONG_SHIFT);
	rtw_write16(padapter, REG_RL, val16);
}