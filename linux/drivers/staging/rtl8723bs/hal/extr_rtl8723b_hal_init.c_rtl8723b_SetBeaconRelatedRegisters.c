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
typedef  int /*<<< orphan*/  u32 ;
struct mlme_ext_info {int bcn_interval; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {int /*<<< orphan*/  mlmepriv; struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int DIS_BCNQ_SUB ; 
 int /*<<< orphan*/  REG_ATIMWND ; 
 int /*<<< orphan*/  REG_BCN_CTRL ; 
 int /*<<< orphan*/  REG_BCN_INTERVAL ; 
 int /*<<< orphan*/  REG_RXTSF_OFFSET_CCK ; 
 int /*<<< orphan*/  REG_RXTSF_OFFSET_OFDM ; 
 int /*<<< orphan*/  REG_SLOT ; 
 int /*<<< orphan*/  REG_TCR ; 
 int /*<<< orphan*/  ResumeTxBeacon (struct adapter*) ; 
 int /*<<< orphan*/  TSFRST ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 int /*<<< orphan*/  _BeaconFunctionEnable (struct adapter*,int,int) ; 
 int check_fwstate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl8723b_InitBeaconParameters (struct adapter*) ; 
 int /*<<< orphan*/  rtw_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int rtw_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write16 (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8723b_SetBeaconRelatedRegisters(struct adapter *padapter)
{
	u8 val8;
	u32 value32;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u32 bcn_ctrl_reg;

	/* reset TSF, enable update TSF, correcting TSF On Beacon */

	/* REG_BCN_INTERVAL */
	/* REG_BCNDMATIM */
	/* REG_ATIMWND */
	/* REG_TBTT_PROHIBIT */
	/* REG_DRVERLYINT */
	/* REG_BCN_MAX_ERR */
	/* REG_BCNTCFG (0x510) */
	/* REG_DUAL_TSF_RST */
	/* REG_BCN_CTRL (0x550) */


	bcn_ctrl_reg = REG_BCN_CTRL;

	/*  */
	/*  ATIM window */
	/*  */
	rtw_write16(padapter, REG_ATIMWND, 2);

	/*  */
	/*  Beacon interval (in unit of TU). */
	/*  */
	rtw_write16(padapter, REG_BCN_INTERVAL, pmlmeinfo->bcn_interval);

	rtl8723b_InitBeaconParameters(padapter);

	rtw_write8(padapter, REG_SLOT, 0x09);

	/*  */
	/*  Reset TSF Timer to zero, added by Roger. 2008.06.24 */
	/*  */
	value32 = rtw_read32(padapter, REG_TCR);
	value32 &= ~TSFRST;
	rtw_write32(padapter, REG_TCR, value32);

	value32 |= TSFRST;
	rtw_write32(padapter, REG_TCR, value32);

	/*  NOTE: Fix test chip's bug (about contention windows's randomness) */
	if (check_fwstate(&padapter->mlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE|WIFI_AP_STATE) == true) {
		rtw_write8(padapter, REG_RXTSF_OFFSET_CCK, 0x50);
		rtw_write8(padapter, REG_RXTSF_OFFSET_OFDM, 0x50);
	}

	_BeaconFunctionEnable(padapter, true, true);

	ResumeTxBeacon(padapter);
	val8 = rtw_read8(padapter, bcn_ctrl_reg);
	val8 |= DIS_BCNQ_SUB;
	rtw_write8(padapter, bcn_ctrl_reg, val8);
}