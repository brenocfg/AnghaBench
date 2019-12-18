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

/* Variables and functions */
#define  DP_LINK_BW_1_62 131 
#define  DP_LINK_BW_2_7 130 
#define  DP_LINK_BW_5_4 129 
#define  DP_LINK_BW_8_1 128 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 

__attribute__((used)) static bool drm_dp_get_vc_payload_bw(int dp_link_bw,
				     int dp_link_count,
				     int *out)
{
	switch (dp_link_bw) {
	default:
		DRM_DEBUG_KMS("invalid link bandwidth in DPCD: %x (link count: %d)\n",
			      dp_link_bw, dp_link_count);
		return false;

	case DP_LINK_BW_1_62:
		*out = 3 * dp_link_count;
		break;
	case DP_LINK_BW_2_7:
		*out = 5 * dp_link_count;
		break;
	case DP_LINK_BW_5_4:
		*out = 10 * dp_link_count;
		break;
	case DP_LINK_BW_8_1:
		*out = 15 * dp_link_count;
		break;
	}
	return true;
}