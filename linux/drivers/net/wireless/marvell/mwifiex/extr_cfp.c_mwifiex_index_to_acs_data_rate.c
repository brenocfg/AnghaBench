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
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int MWIFIEX_RATE_BITMAP_MCS0 ; 
 int MWIFIEX_RATE_FORMAT_HT ; 
 int MWIFIEX_RATE_FORMAT_VHT ; 
 int MWIFIEX_SUPPORTED_RATES_EXT ; 
 int** ac_mcs_rate_nss1 ; 
 int** ac_mcs_rate_nss2 ; 
 int** mcs_rate ; 
 int min (int,int) ; 
 int* mwifiex_data_rates ; 

u32 mwifiex_index_to_acs_data_rate(struct mwifiex_private *priv,
				   u8 index, u8 ht_info)
{
	u32 rate = 0;
	u8 mcs_index = 0;
	u8 bw = 0;
	u8 gi = 0;

	if ((ht_info & 0x3) == MWIFIEX_RATE_FORMAT_VHT) {
		mcs_index = min(index & 0xF, 9);

		/* 20M: bw=0, 40M: bw=1, 80M: bw=2, 160M: bw=3 */
		bw = (ht_info & 0xC) >> 2;

		/* LGI: gi =0, SGI: gi = 1 */
		gi = (ht_info & 0x10) >> 4;

		if ((index >> 4) == 1)	/* NSS = 2 */
			rate = ac_mcs_rate_nss2[2 * (3 - bw) + gi][mcs_index];
		else			/* NSS = 1 */
			rate = ac_mcs_rate_nss1[2 * (3 - bw) + gi][mcs_index];
	} else if ((ht_info & 0x3) == MWIFIEX_RATE_FORMAT_HT) {
		/* 20M: bw=0, 40M: bw=1 */
		bw = (ht_info & 0xC) >> 2;

		/* LGI: gi =0, SGI: gi = 1 */
		gi = (ht_info & 0x10) >> 4;

		if (index == MWIFIEX_RATE_BITMAP_MCS0) {
			if (gi == 1)
				rate = 0x0D;    /* MCS 32 SGI rate */
			else
				rate = 0x0C;    /* MCS 32 LGI rate */
		} else if (index < 16) {
			if ((bw == 1) || (bw == 0))
				rate = mcs_rate[2 * (1 - bw) + gi][index];
			else
				rate = mwifiex_data_rates[0];
		} else {
			rate = mwifiex_data_rates[0];
		}
	} else {
		/* 11n non-HT rates */
		if (index >= MWIFIEX_SUPPORTED_RATES_EXT)
			index = 0;
		rate = mwifiex_data_rates[index];
	}

	return rate;
}