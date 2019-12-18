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
typedef  int u32 ;
typedef  enum hw_atl_fw2x_rate { ____Placeholder_hw_atl_fw2x_rate } hw_atl_fw2x_rate ;

/* Variables and functions */
 int AQ_NIC_RATE_EEE_10G ; 
 int AQ_NIC_RATE_EEE_1G ; 
 int AQ_NIC_RATE_EEE_2GS ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_2500baseX_Full ; 

__attribute__((used)) static enum hw_atl_fw2x_rate eee_mask_to_ethtool_mask(u32 speed)
{
	u32 rate = 0;

	if (speed & AQ_NIC_RATE_EEE_10G)
		rate |= SUPPORTED_10000baseT_Full;

	if (speed & AQ_NIC_RATE_EEE_2GS)
		rate |= SUPPORTED_2500baseX_Full;

	if (speed & AQ_NIC_RATE_EEE_1G)
		rate |= SUPPORTED_1000baseT_Full;

	return rate;
}