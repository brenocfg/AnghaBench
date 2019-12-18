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
struct wcn36xx_hal_config_sta_params {int ht_capable; int tx_channel_width_set; int lsig_txop_protection; int max_ampdu_size; int max_ampdu_density; int sgi_20Mhz; int sgi_40mhz; int green_field_capable; int dsss_cck_mode_40mhz; scalar_t__ delayed_ba_support; scalar_t__ max_amsdu_size; } ;

/* Variables and functions */

__attribute__((used)) static void wcn36xx_smd_set_sta_default_ht_params(
		struct wcn36xx_hal_config_sta_params *sta_params)
{
	sta_params->ht_capable = 1;
	sta_params->tx_channel_width_set = 1;
	sta_params->lsig_txop_protection = 1;
	sta_params->max_ampdu_size = 3;
	sta_params->max_ampdu_density = 5;
	sta_params->max_amsdu_size = 0;
	sta_params->sgi_20Mhz = 1;
	sta_params->sgi_40mhz = 1;
	sta_params->green_field_capable = 1;
	sta_params->delayed_ba_support = 0;
	sta_params->dsss_cck_mode_40mhz = 1;
}