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
typedef  size_t u8 ;
struct hal_com_data {scalar_t__***** TxPwrLimit_5G; } ;
struct adapter {int dummy; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 size_t CHANNEL_MAX_NUMBER_5G ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 size_t MAX_5G_BANDWITH_NUM ; 
 scalar_t__ MAX_POWER_INDEX ; 
 size_t MAX_RATE_SECTION_NUM ; 
 size_t MAX_REGULATION_NUM ; 
 size_t ODM_RF_PATH_A ; 

__attribute__((used)) static void phy_CrossReferenceHTAndVHTTxPowerLimit(struct adapter *padapter)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u8 regulation, bw, channel, rateSection;
	s8 tempPwrLmt = 0;

	for (regulation = 0; regulation < MAX_REGULATION_NUM; ++regulation) {
		for (bw = 0; bw < MAX_5G_BANDWITH_NUM; ++bw) {
			for (channel = 0; channel < CHANNEL_MAX_NUMBER_5G; ++channel) {
				for (rateSection = 0; rateSection < MAX_RATE_SECTION_NUM; ++rateSection) {
					tempPwrLmt = pHalData->TxPwrLimit_5G[regulation][bw][rateSection][channel][ODM_RF_PATH_A];
					if (tempPwrLmt == MAX_POWER_INDEX) {
						u8 baseSection = 2, refSection = 6;
						if (bw == 0 || bw == 1) { /*  5G 20M 40M VHT and HT can cross reference */
							/* DBG_871X("No power limit table of the specified band %d, bandwidth %d, ratesection %d, channel %d, rf path %d\n", */
							/*			1, bw, rateSection, channel, ODM_RF_PATH_A); */
							if (rateSection >= 2 && rateSection <= 9) {
								if (rateSection == 2) {
									baseSection = 2;
									refSection = 6;
								} else if (rateSection == 3) {
									baseSection = 3;
									refSection = 7;
								} else if (rateSection == 4) {
									baseSection = 4;
									refSection = 8;
								} else if (rateSection == 5) {
									baseSection = 5;
									refSection = 9;
								} else if (rateSection == 6) {
									baseSection = 6;
									refSection = 2;
								} else if (rateSection == 7) {
									baseSection = 7;
									refSection = 3;
								} else if (rateSection == 8) {
									baseSection = 8;
									refSection = 4;
								} else if (rateSection == 9) {
									baseSection = 9;
									refSection = 5;
								}
								pHalData->TxPwrLimit_5G[regulation][bw][baseSection][channel][ODM_RF_PATH_A] =
									pHalData->TxPwrLimit_5G[regulation][bw][refSection][channel][ODM_RF_PATH_A];
							}

							/* DBG_871X("use other value %d", tempPwrLmt); */
						}
					}
				}
			}
		}
	}
}