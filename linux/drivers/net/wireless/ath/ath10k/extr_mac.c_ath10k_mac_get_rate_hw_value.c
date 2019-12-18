#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int bitrate; int hw_value; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int WMI_RATE_PREAMBLE_CCK ; 
 scalar_t__ ath10k_mac_bitrate_is_cck (int) ; 
 TYPE_1__* ath10k_rates ; 

__attribute__((used)) static int ath10k_mac_get_rate_hw_value(int bitrate)
{
	int i;
	u8 hw_value_prefix = 0;

	if (ath10k_mac_bitrate_is_cck(bitrate))
		hw_value_prefix = WMI_RATE_PREAMBLE_CCK << 6;

	for (i = 0; i < ARRAY_SIZE(ath10k_rates); i++) {
		if (ath10k_rates[i].bitrate == bitrate)
			return hw_value_prefix | ath10k_rates[i].hw_value;
	}

	return -EINVAL;
}