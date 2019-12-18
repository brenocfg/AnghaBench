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
struct hal_data_8188e {int* RfRegChnlVal; } ;
struct adapter {struct hal_data_8188e* HalData; } ;
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;

/* Variables and functions */
 int BIT (int) ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_40 128 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  bRFRegOffsetMask ; 
 int /*<<< orphan*/  phy_set_rf_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void rtl88eu_phy_rf6052_set_bandwidth(struct adapter *adapt,
				      enum ht_channel_width bandwidth)
{
	struct hal_data_8188e *hal_data = adapt->HalData;

	switch (bandwidth) {
	case HT_CHANNEL_WIDTH_20:
		hal_data->RfRegChnlVal[0] = ((hal_data->RfRegChnlVal[0] &
					      0xfffff3ff) | BIT(10) | BIT(11));
		phy_set_rf_reg(adapt, RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask,
			       hal_data->RfRegChnlVal[0]);
		break;
	case HT_CHANNEL_WIDTH_40:
		hal_data->RfRegChnlVal[0] = ((hal_data->RfRegChnlVal[0] &
					      0xfffff3ff) | BIT(10));
		phy_set_rf_reg(adapt, RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask,
			       hal_data->RfRegChnlVal[0]);
		break;
	default:
		break;
	}
}