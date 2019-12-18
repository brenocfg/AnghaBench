#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_3__ {int bpc; void* vdisplay; void* hdisplay; scalar_t__ video_pattern; } ;
struct TYPE_4__ {int test_active; TYPE_1__ test_data; } ;
struct intel_dp {TYPE_2__ compliance; int /*<<< orphan*/  aux; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ DP_COLOR_FORMAT_RGB ; 
 scalar_t__ DP_COLOR_RAMP ; 
 scalar_t__ DP_TEST_ACK ; 
#define  DP_TEST_BIT_DEPTH_6 129 
#define  DP_TEST_BIT_DEPTH_8 128 
 scalar_t__ DP_TEST_BIT_DEPTH_MASK ; 
 scalar_t__ DP_TEST_COLOR_FORMAT_MASK ; 
 scalar_t__ DP_TEST_DYNAMIC_RANGE_CEA ; 
 int /*<<< orphan*/  DP_TEST_H_WIDTH_HI ; 
 int /*<<< orphan*/  DP_TEST_MISC0 ; 
 scalar_t__ DP_TEST_NAK ; 
 int /*<<< orphan*/  DP_TEST_PATTERN ; 
 int /*<<< orphan*/  DP_TEST_V_HEIGHT_HI ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static u8 intel_dp_autotest_video_pattern(struct intel_dp *intel_dp)
{
	u8 test_pattern;
	u8 test_misc;
	__be16 h_width, v_height;
	int status = 0;

	/* Read the TEST_PATTERN (DP CTS 3.1.5) */
	status = drm_dp_dpcd_readb(&intel_dp->aux, DP_TEST_PATTERN,
				   &test_pattern);
	if (status <= 0) {
		DRM_DEBUG_KMS("Test pattern read failed\n");
		return DP_TEST_NAK;
	}
	if (test_pattern != DP_COLOR_RAMP)
		return DP_TEST_NAK;

	status = drm_dp_dpcd_read(&intel_dp->aux, DP_TEST_H_WIDTH_HI,
				  &h_width, 2);
	if (status <= 0) {
		DRM_DEBUG_KMS("H Width read failed\n");
		return DP_TEST_NAK;
	}

	status = drm_dp_dpcd_read(&intel_dp->aux, DP_TEST_V_HEIGHT_HI,
				  &v_height, 2);
	if (status <= 0) {
		DRM_DEBUG_KMS("V Height read failed\n");
		return DP_TEST_NAK;
	}

	status = drm_dp_dpcd_readb(&intel_dp->aux, DP_TEST_MISC0,
				   &test_misc);
	if (status <= 0) {
		DRM_DEBUG_KMS("TEST MISC read failed\n");
		return DP_TEST_NAK;
	}
	if ((test_misc & DP_TEST_COLOR_FORMAT_MASK) != DP_COLOR_FORMAT_RGB)
		return DP_TEST_NAK;
	if (test_misc & DP_TEST_DYNAMIC_RANGE_CEA)
		return DP_TEST_NAK;
	switch (test_misc & DP_TEST_BIT_DEPTH_MASK) {
	case DP_TEST_BIT_DEPTH_6:
		intel_dp->compliance.test_data.bpc = 6;
		break;
	case DP_TEST_BIT_DEPTH_8:
		intel_dp->compliance.test_data.bpc = 8;
		break;
	default:
		return DP_TEST_NAK;
	}

	intel_dp->compliance.test_data.video_pattern = test_pattern;
	intel_dp->compliance.test_data.hdisplay = be16_to_cpu(h_width);
	intel_dp->compliance.test_data.vdisplay = be16_to_cpu(v_height);
	/* Set test active flag here so userspace doesn't interrupt things */
	intel_dp->compliance.test_active = 1;

	return DP_TEST_ACK;
}