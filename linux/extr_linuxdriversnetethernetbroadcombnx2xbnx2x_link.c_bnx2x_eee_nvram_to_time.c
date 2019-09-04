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
 int EEE_MODE_NVRAM_AGGRESSIVE_TIME ; 
 int EEE_MODE_NVRAM_BALANCED_TIME ; 
 int EEE_MODE_NVRAM_LATENCY_TIME ; 
#define  PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE 130 
#define  PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED 129 
#define  PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY 128 

__attribute__((used)) static int bnx2x_eee_nvram_to_time(u32 nvram_mode, u32 *idle_timer)
{
	switch (nvram_mode) {
	case PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED:
		*idle_timer = EEE_MODE_NVRAM_BALANCED_TIME;
		break;
	case PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE:
		*idle_timer = EEE_MODE_NVRAM_AGGRESSIVE_TIME;
		break;
	case PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY:
		*idle_timer = EEE_MODE_NVRAM_LATENCY_TIME;
		break;
	default:
		*idle_timer = 0;
		break;
	}

	return 0;
}