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
struct TYPE_2__ {scalar_t__* swing_idx_ofdm; scalar_t__* swing_idx_ofdm_base; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct rtl_dm {int* swing_idx_ofdm_base; int* swing_idx_ofdm; scalar_t__ swing_idx_cck; scalar_t__ swing_idx_cck_base; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t RF90_PATH_A ; 
 int TXPWRTRACK_MAX_IDX ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8821ae_dm_txpower_track_adjust(struct ieee80211_hw *hw,
				       u8 type, u8 *pdirection,
				       u32 *poutwrite_val)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	u8 pwr_val = 0;

	if (type == 0) {
		if (rtlpriv->dm.swing_idx_ofdm[RF90_PATH_A] <=
			rtlpriv->dm.swing_idx_ofdm_base[RF90_PATH_A]) {
			*pdirection = 1;
			pwr_val = rtldm->swing_idx_ofdm_base[RF90_PATH_A] -
					rtldm->swing_idx_ofdm[RF90_PATH_A];
		} else {
			*pdirection = 2;
			pwr_val = rtldm->swing_idx_ofdm[RF90_PATH_A] -
				rtldm->swing_idx_ofdm_base[RF90_PATH_A];
		}
	} else if (type == 1) {
		if (rtldm->swing_idx_cck <= rtldm->swing_idx_cck_base) {
			*pdirection = 1;
			pwr_val = rtldm->swing_idx_cck_base -
					rtldm->swing_idx_cck;
		} else {
			*pdirection = 2;
			pwr_val = rtldm->swing_idx_cck -
				rtldm->swing_idx_cck_base;
		}
	}

	if (pwr_val >= TXPWRTRACK_MAX_IDX && (*pdirection == 1))
		pwr_val = TXPWRTRACK_MAX_IDX;

	*poutwrite_val = pwr_val | (pwr_val << 8)|
				(pwr_val << 16)|
				(pwr_val << 24);
}