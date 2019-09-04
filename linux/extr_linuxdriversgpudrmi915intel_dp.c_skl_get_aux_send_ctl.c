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
typedef  int uint32_t ;
struct intel_dp {int dummy; } ;

/* Variables and functions */
 int DP_AUX_CH_CTL_DONE ; 
 int DP_AUX_CH_CTL_FW_SYNC_PULSE_SKL (int) ; 
 int DP_AUX_CH_CTL_INTERRUPT ; 
 int DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT ; 
 int DP_AUX_CH_CTL_RECEIVE_ERROR ; 
 int DP_AUX_CH_CTL_SEND_BUSY ; 
 int DP_AUX_CH_CTL_SYNC_PULSE_SKL (int) ; 
 int DP_AUX_CH_CTL_TIME_OUT_ERROR ; 
 int DP_AUX_CH_CTL_TIME_OUT_MAX ; 

__attribute__((used)) static uint32_t skl_get_aux_send_ctl(struct intel_dp *intel_dp,
				      int send_bytes,
				      uint32_t unused)
{
	return DP_AUX_CH_CTL_SEND_BUSY |
	       DP_AUX_CH_CTL_DONE |
	       DP_AUX_CH_CTL_INTERRUPT |
	       DP_AUX_CH_CTL_TIME_OUT_ERROR |
	       DP_AUX_CH_CTL_TIME_OUT_MAX |
	       DP_AUX_CH_CTL_RECEIVE_ERROR |
	       (send_bytes << DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT) |
	       DP_AUX_CH_CTL_FW_SYNC_PULSE_SKL(32) |
	       DP_AUX_CH_CTL_SYNC_PULSE_SKL(32);
}