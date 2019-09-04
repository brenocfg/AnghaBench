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
 int AQ_NIC_RATE_100M ; 
 int AQ_NIC_RATE_10G ; 
 int AQ_NIC_RATE_1G ; 
 int AQ_NIC_RATE_2GS ; 
 int AQ_NIC_RATE_5G ; 
 int AQ_NIC_RATE_5GSR ; 
 int FW2X_RATE_100M ; 
 int FW2X_RATE_10G ; 
 int FW2X_RATE_1G ; 
 int FW2X_RATE_2G5 ; 
 int FW2X_RATE_5G ; 

__attribute__((used)) static enum hw_atl_fw2x_rate link_speed_mask_2fw2x_ratemask(u32 speed)
{
	enum hw_atl_fw2x_rate rate = 0;

	if (speed & AQ_NIC_RATE_10G)
		rate |= FW2X_RATE_10G;

	if (speed & AQ_NIC_RATE_5G)
		rate |= FW2X_RATE_5G;

	if (speed & AQ_NIC_RATE_5GSR)
		rate |= FW2X_RATE_5G;

	if (speed & AQ_NIC_RATE_2GS)
		rate |= FW2X_RATE_2G5;

	if (speed & AQ_NIC_RATE_1G)
		rate |= FW2X_RATE_1G;

	if (speed & AQ_NIC_RATE_100M)
		rate |= FW2X_RATE_100M;

	return rate;
}