#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int test_type; } ;
struct intel_dp {int /*<<< orphan*/  aux; TYPE_1__ compliance; } ;

/* Variables and functions */
 int DP_TEST_ACK ; 
#define  DP_TEST_LINK_EDID_READ 131 
#define  DP_TEST_LINK_PHY_TEST_PATTERN 130 
#define  DP_TEST_LINK_TRAINING 129 
#define  DP_TEST_LINK_VIDEO_PATTERN 128 
 int DP_TEST_NAK ; 
 int /*<<< orphan*/  DP_TEST_REQUEST ; 
 int /*<<< orphan*/  DP_TEST_RESPONSE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int intel_dp_autotest_edid (struct intel_dp*) ; 
 int intel_dp_autotest_link_training (struct intel_dp*) ; 
 int intel_dp_autotest_phy_pattern (struct intel_dp*) ; 
 int intel_dp_autotest_video_pattern (struct intel_dp*) ; 

__attribute__((used)) static void intel_dp_handle_test_request(struct intel_dp *intel_dp)
{
	u8 response = DP_TEST_NAK;
	u8 request = 0;
	int status;

	status = drm_dp_dpcd_readb(&intel_dp->aux, DP_TEST_REQUEST, &request);
	if (status <= 0) {
		DRM_DEBUG_KMS("Could not read test request from sink\n");
		goto update_status;
	}

	switch (request) {
	case DP_TEST_LINK_TRAINING:
		DRM_DEBUG_KMS("LINK_TRAINING test requested\n");
		response = intel_dp_autotest_link_training(intel_dp);
		break;
	case DP_TEST_LINK_VIDEO_PATTERN:
		DRM_DEBUG_KMS("TEST_PATTERN test requested\n");
		response = intel_dp_autotest_video_pattern(intel_dp);
		break;
	case DP_TEST_LINK_EDID_READ:
		DRM_DEBUG_KMS("EDID test requested\n");
		response = intel_dp_autotest_edid(intel_dp);
		break;
	case DP_TEST_LINK_PHY_TEST_PATTERN:
		DRM_DEBUG_KMS("PHY_PATTERN test requested\n");
		response = intel_dp_autotest_phy_pattern(intel_dp);
		break;
	default:
		DRM_DEBUG_KMS("Invalid test request '%02x'\n", request);
		break;
	}

	if (response & DP_TEST_ACK)
		intel_dp->compliance.test_type = request;

update_status:
	status = drm_dp_dpcd_writeb(&intel_dp->aux, DP_TEST_RESPONSE, response);
	if (status <= 0)
		DRM_DEBUG_KMS("Could not write test response to sink\n");
}