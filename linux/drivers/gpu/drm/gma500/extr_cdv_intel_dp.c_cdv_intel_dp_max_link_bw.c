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
struct gma_encoder {struct cdv_intel_dp* dev_priv; } ;
struct cdv_intel_dp {int* dpcd; } ;

/* Variables and functions */
#define  DP_LINK_BW_1_62 129 
#define  DP_LINK_BW_2_7 128 
 size_t DP_MAX_LINK_RATE ; 

__attribute__((used)) static int
cdv_intel_dp_max_link_bw(struct gma_encoder *encoder)
{
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	int max_link_bw = intel_dp->dpcd[DP_MAX_LINK_RATE];

	switch (max_link_bw) {
	case DP_LINK_BW_1_62:
	case DP_LINK_BW_2_7:
		break;
	default:
		max_link_bw = DP_LINK_BW_1_62;
		break;
	}
	return max_link_bw;
}