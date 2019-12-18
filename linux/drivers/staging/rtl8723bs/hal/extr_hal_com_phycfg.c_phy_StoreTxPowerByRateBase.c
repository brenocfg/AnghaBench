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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 int /*<<< orphan*/  BAND_ON_5G ; 
 int /*<<< orphan*/  CCK ; 
 int /*<<< orphan*/  HT_MCS0_MCS7 ; 
 int /*<<< orphan*/  HT_MCS16_MCS23 ; 
 int /*<<< orphan*/  HT_MCS8_MCS15 ; 
 int /*<<< orphan*/  MGN_11M ; 
 int /*<<< orphan*/  MGN_54M ; 
 int /*<<< orphan*/  MGN_MCS15 ; 
 int /*<<< orphan*/  MGN_MCS23 ; 
 int /*<<< orphan*/  MGN_MCS7 ; 
 int /*<<< orphan*/  MGN_VHT1SS_MCS7 ; 
 int /*<<< orphan*/  MGN_VHT2SS_MCS7 ; 
 int /*<<< orphan*/  MGN_VHT3SS_MCS7 ; 
 scalar_t__ ODM_RF_PATH_A ; 
 scalar_t__ ODM_RF_PATH_B ; 
 int /*<<< orphan*/  OFDM ; 
 scalar_t__ PHY_GetTxPowerByRate (struct adapter*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_1TX ; 
 int /*<<< orphan*/  RF_2TX ; 
 int /*<<< orphan*/  RF_3TX ; 
 int /*<<< orphan*/  VHT_1SSMCS0_1SSMCS9 ; 
 int /*<<< orphan*/  VHT_2SSMCS0_2SSMCS9 ; 
 int /*<<< orphan*/  VHT_3SSMCS0_3SSMCS9 ; 
 int /*<<< orphan*/  phy_SetTxPowerByRateBase (struct adapter*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
phy_StoreTxPowerByRateBase(
struct adapter *padapter
	)
{
	u8 path, base;

	/* DBG_871X("===>%s\n", __func__); */

	for (path = ODM_RF_PATH_A; path <= ODM_RF_PATH_B; ++path) {
		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_1TX, MGN_11M);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, CCK, RF_1TX, base);
		/* DBG_871X("Power index base of 2.4G path %d 1Tx CCK = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_1TX, MGN_54M);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, OFDM, RF_1TX, base);
		/* DBG_871X("Power index base of 2.4G path %d 1Tx OFDM = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_1TX, MGN_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, HT_MCS0_MCS7, RF_1TX, base);
		/* DBG_871X("Power index base of 2.4G path %d 1Tx MCS0-7 = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_2TX, MGN_MCS15);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, HT_MCS8_MCS15, RF_2TX, base);
		/* DBG_871X("Power index base of 2.4G path %d 2Tx MCS8-15 = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_3TX, MGN_MCS23);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, HT_MCS16_MCS23, RF_3TX, base);
		/* DBG_871X("Power index base of 2.4G path %d 3Tx MCS16-23 = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_1TX, MGN_VHT1SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, VHT_1SSMCS0_1SSMCS9, RF_1TX, base);
		/* DBG_871X("Power index base of 2.4G path %d 1Tx VHT1SS = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_2TX, MGN_VHT2SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, VHT_2SSMCS0_2SSMCS9, RF_2TX, base);
		/* DBG_871X("Power index base of 2.4G path %d 2Tx VHT2SS = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_3TX, MGN_VHT3SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, VHT_3SSMCS0_3SSMCS9, RF_3TX, base);
		/* DBG_871X("Power index base of 2.4G path %d 3Tx VHT3SS = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_1TX, MGN_54M);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, OFDM, RF_1TX, base);
		/* DBG_871X("Power index base of 5G path %d 1Tx OFDM = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_1TX, MGN_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, HT_MCS0_MCS7, RF_1TX, base);
		/* DBG_871X("Power index base of 5G path %d 1Tx MCS0~7 = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_2TX, MGN_MCS15);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, HT_MCS8_MCS15, RF_2TX, base);
		/* DBG_871X("Power index base of 5G path %d 2Tx MCS8~15 = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_3TX, MGN_MCS23);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, HT_MCS16_MCS23, RF_3TX, base);
		/* DBG_871X("Power index base of 5G path %d 3Tx MCS16~23 = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_1TX, MGN_VHT1SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, VHT_1SSMCS0_1SSMCS9, RF_1TX, base);
		/* DBG_871X("Power index base of 5G path %d 1Tx VHT1SS = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_2TX, MGN_VHT2SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, VHT_2SSMCS0_2SSMCS9, RF_2TX, base);
		/* DBG_871X("Power index base of 5G path %d 2Tx VHT2SS = > 0x%x\n", path, base); */

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_3TX, MGN_VHT2SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, VHT_3SSMCS0_3SSMCS9, RF_3TX, base);
		/* DBG_871X("Power index base of 5G path %d 3Tx VHT3SS = > 0x%x\n", path, base); */
	}

	/* DBG_871X("<===%s\n", __func__); */
}