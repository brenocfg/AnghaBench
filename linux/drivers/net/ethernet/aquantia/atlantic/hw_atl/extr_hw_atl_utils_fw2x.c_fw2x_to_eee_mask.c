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

/* Variables and functions */
 int AQ_NIC_RATE_EEE_10G ; 
 int AQ_NIC_RATE_EEE_1G ; 
 int AQ_NIC_RATE_EEE_2GS ; 
 int AQ_NIC_RATE_EEE_5G ; 
 int HW_ATL_FW2X_CAP_EEE_10G_MASK ; 
 int HW_ATL_FW2X_CAP_EEE_1G_MASK ; 
 int HW_ATL_FW2X_CAP_EEE_2G5_MASK ; 
 int HW_ATL_FW2X_CAP_EEE_5G_MASK ; 

__attribute__((used)) static u32 fw2x_to_eee_mask(u32 speed)
{
	u32 rate = 0;

	if (speed & HW_ATL_FW2X_CAP_EEE_10G_MASK)
		rate |= AQ_NIC_RATE_EEE_10G;
	if (speed & HW_ATL_FW2X_CAP_EEE_5G_MASK)
		rate |= AQ_NIC_RATE_EEE_5G;
	if (speed & HW_ATL_FW2X_CAP_EEE_2G5_MASK)
		rate |= AQ_NIC_RATE_EEE_2GS;
	if (speed & HW_ATL_FW2X_CAP_EEE_1G_MASK)
		rate |= AQ_NIC_RATE_EEE_1G;

	return rate;
}