#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int* supp_mcs_set; } ;
struct TYPE_4__ {TYPE_1__ ht_cap; scalar_t__ ht_option; } ;
struct sta_info {int* bssrateset; int ra_mask; int init_rate; TYPE_2__ htpriv; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  HW_VAR_RF_TYPE ; 
 int RF_2T2R ; 
 int get_highest_rate_idx (int) ; 
 int rtw_get_bit_value_from_ieee_value (int) ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,int*) ; 

void rtw_hal_update_sta_rate_mask(struct adapter *padapter, struct sta_info *psta)
{
	u8 i, rf_type, limit;
	u32 tx_ra_bitmap;

	if (!psta)
		return;

	tx_ra_bitmap = 0;

	/* b/g mode ra_bitmap */
	for (i = 0; i < sizeof(psta->bssrateset); i++) {
		if (psta->bssrateset[i])
			tx_ra_bitmap |= rtw_get_bit_value_from_ieee_value(psta->bssrateset[i]&0x7f);
	}

	/* n mode ra_bitmap */
	if (psta->htpriv.ht_option) {
		rtw_hal_get_hwreg(padapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));
		if (rf_type == RF_2T2R)
			limit = 16; /*  2R */
		else
			limit = 8; /*   1R */

		for (i = 0; i < limit; i++) {
			if (psta->htpriv.ht_cap.supp_mcs_set[i/8] & BIT(i%8))
				tx_ra_bitmap |= BIT(i+12);
		}
	}

	psta->ra_mask = tx_ra_bitmap;
	psta->init_rate = get_highest_rate_idx(tx_ra_bitmap)&0x3f;
}