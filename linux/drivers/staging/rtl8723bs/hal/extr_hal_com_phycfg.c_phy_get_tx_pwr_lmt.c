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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hal_com_data {int EEPROMRegulatory; int Regulation2_4G; int Regulation5G; int /*<<< orphan*/ ***** TxPwrLimit_5G; int /*<<< orphan*/ ***** TxPwrLimit_2_4G; } ;
struct TYPE_2__ {int RegEnableTxPowerLimit; int RegPwrTblSel; } ;
struct adapter {TYPE_1__ registrypriv; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int s16 ;
typedef  enum CHANNEL_WIDTH { ____Placeholder_CHANNEL_WIDTH } CHANNEL_WIDTH ;
typedef  enum BAND_TYPE { ____Placeholder_BAND_TYPE } BAND_TYPE ;

/* Variables and functions */
 int BAND_ON_2_4G ; 
 int BAND_ON_5G ; 
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int /*<<< orphan*/  DataRate ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  MAX_POWER_INDEX ; 
 size_t MAX_REGULATION_NUM ; 
 int TXPWR_LMT_ETSI ; 
 int TXPWR_LMT_FCC ; 
 int TXPWR_LMT_MKK ; 
 int TXPWR_LMT_WW ; 
 int get_bandwidth_idx (int) ; 
 int get_rate_sctn_idx (size_t) ; 
 size_t phy_GetChannelIndexOfTxPowerLimit (int,size_t) ; 
 int /*<<< orphan*/  phy_GetWorldWideLimit (int /*<<< orphan*/ *) ; 

s8 phy_get_tx_pwr_lmt(struct adapter *adapter, u32 reg_pwr_tbl_sel,
		      enum BAND_TYPE band_type, enum CHANNEL_WIDTH bandwidth,
		      u8 rf_path, u8 data_rate, u8 channel)
{
	s16 idx_band       = -1;
	s16 idx_regulation = -1;
	s16 idx_bandwidth  = -1;
	s16 idx_rate_sctn  = -1;
	s16 idx_channel    = -1;
	s8 pwr_lmt = MAX_POWER_INDEX;
	struct hal_com_data *hal_data = GET_HAL_DATA(adapter);

	if (((adapter->registrypriv.RegEnableTxPowerLimit == 2) &&
	     (hal_data->EEPROMRegulatory != 1)) ||
	    (adapter->registrypriv.RegEnableTxPowerLimit == 0))
		return MAX_POWER_INDEX;

	switch (adapter->registrypriv.RegPwrTblSel) {
	case 1:
		idx_regulation = TXPWR_LMT_ETSI;
		break;
	case 2:
		idx_regulation = TXPWR_LMT_MKK;
		break;
	case 3:
		idx_regulation = TXPWR_LMT_FCC;
		break;
	case 4:
		idx_regulation = TXPWR_LMT_WW;
		break;
	default:
		idx_regulation = (band_type == BAND_ON_2_4G) ?
			hal_data->Regulation2_4G :
			hal_data->Regulation5G;
		break;
	}

	/* DBG_871X("pMgntInfo->RegPwrTblSel %d, final regulation %d\n", */
	/*         adapter->registrypriv.RegPwrTblSel, idx_regulation); */

	if (band_type == BAND_ON_2_4G)
		idx_band = 0;
	else if (band_type == BAND_ON_5G)
		idx_band = 1;

	idx_bandwidth = get_bandwidth_idx(bandwidth);
	idx_rate_sctn = get_rate_sctn_idx(data_rate);

	if (band_type == BAND_ON_5G && idx_rate_sctn == 0)
		DBG_871X("Wrong rate 0x%x: No CCK in 5G Band\n", DataRate);

	/*  workaround for wrong index combination to obtain tx power limit, */
	/*  OFDM only exists in BW 20M */
	/*  CCK table will only be given in BW 20M */
	/*  HT on 80M will reference to HT on 40M */
	if (idx_rate_sctn == 0 || idx_rate_sctn == 1)
		idx_bandwidth = 0;
	else if ((idx_rate_sctn == 2 || idx_rate_sctn == 3) &&
		 (band_type == BAND_ON_5G) && (idx_bandwidth == 2))
		idx_bandwidth = 1;

	if (band_type == BAND_ON_2_4G || band_type == BAND_ON_5G)
		channel = phy_GetChannelIndexOfTxPowerLimit(band_type, channel);

	if (idx_band == -1 || idx_regulation == -1 || idx_bandwidth == -1 ||
	    idx_rate_sctn == -1 || idx_channel == -1) {
		/* DBG_871X("Wrong index value to access power limit table [band %d][regulation %d][bandwidth %d][rf_path %d][rate_section %d][chnlGroup %d]\n", */
		/*         idx_band, idx_regulation, idx_bandwidth, rf_path, */
		/*         idx_rate_sctn, channel); */

		return MAX_POWER_INDEX;
	}

	if (band_type == BAND_ON_2_4G) {
		s8 limits[10] = {0}; u8 i = 0;

		for (i = 0; i < MAX_REGULATION_NUM; i++)
			limits[i] = hal_data->TxPwrLimit_2_4G[i]
							     [idx_bandwidth]
							     [idx_rate_sctn]
							     [idx_channel]
							     [rf_path];

		pwr_lmt = (idx_regulation == TXPWR_LMT_WW) ?
			phy_GetWorldWideLimit(limits) :
			hal_data->TxPwrLimit_2_4G[idx_regulation]
						 [idx_bandwidth]
						 [idx_rate_sctn]
						 [idx_channel]
						 [rf_path];

	} else if (band_type == BAND_ON_5G) {
		s8 limits[10] = {0}; u8 i = 0;

		for (i = 0; i < MAX_REGULATION_NUM; ++i)
			limits[i] = hal_data->TxPwrLimit_5G[i]
							   [idx_bandwidth]
							   [idx_rate_sctn]
							   [idx_channel]
							   [rf_path];

		pwr_lmt = (idx_regulation == TXPWR_LMT_WW) ?
			phy_GetWorldWideLimit(limits) :
			hal_data->TxPwrLimit_5G[idx_regulation]
					       [idx_bandwidth]
					       [idx_rate_sctn]
					       [idx_channel]
					       [rf_path];
	} else {
		DBG_871X("No power limit table of the specified band\n");
	}

	/*  combine 5G VHT & HT rate */
	/*  5G 20M and 40M HT and VHT can cross reference */
	/*
	if (band_type == BAND_ON_5G && pwr_lmt == MAX_POWER_INDEX) {
		if (idx_bandwidth == 0 || idx_bandwidth == 1) {
			RT_TRACE(COMP_INIT, DBG_LOUD, ("No power limit table of the specified band %d, bandwidth %d, ratesection %d, rf path %d\n",
				 idx_band, idx_bandwidth,
				 idx_rate_sctn, rf_path));
			if (idx_rate_sctn == 2)
				pwr_lmt = hal_data->TxPwrLimit_5G[idx_regulation][idx_bandwidth][4][idx_channel][rf_path];
			else if (idx_rate_sctn == 4)
				pwr_lmt = hal_data->TxPwrLimit_5G[idx_regulation][idx_bandwidth][2][idx_channel][rf_path];
			else if (idx_rate_sctn == 3)
				pwr_lmt = hal_data->TxPwrLimit_5G[idx_regulation][idx_bandwidth][5][idx_channel][rf_path];
			else if (idx_rate_sctn == 5)
				pwr_lmt = hal_data->TxPwrLimit_5G[idx_regulation][idx_bandwidth][3][idx_channel][rf_path];
		}
	}
	*/

	/* DBG_871X("TxPwrLmt[Regulation %d][Band %d][BW %d][RFPath %d][Rate 0x%x][Chnl %d] = %d\n", */
	/*		idx_regulation, hal_data->CurrentBandType, bandwidth, rf_path, data_rate, channel, pwr_lmt); */
	return pwr_lmt;
}