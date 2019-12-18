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
struct hal_data_8188e {int CurrentChannelBW; unsigned char nCur40MhzPrimeSC; } ;
struct adapter {int /*<<< orphan*/  bSurpriseRemoved; int /*<<< orphan*/  bDriverStopped; struct hal_data_8188e* HalData; } ;
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;

/* Variables and functions */
 int /*<<< orphan*/  phy_set_bw_mode_callback (struct adapter*) ; 

void rtw_hal_set_bwmode(struct adapter *adapt, enum ht_channel_width bandwidth,
		     unsigned char offset)
{
	struct hal_data_8188e *hal_data = adapt->HalData;
	enum ht_channel_width tmp_bw = hal_data->CurrentChannelBW;

	hal_data->CurrentChannelBW = bandwidth;
	hal_data->nCur40MhzPrimeSC = offset;

	if ((!adapt->bDriverStopped) && (!adapt->bSurpriseRemoved))
		phy_set_bw_mode_callback(adapt);
	else
		hal_data->CurrentChannelBW = tmp_bw;
}