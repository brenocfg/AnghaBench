#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  edid; } ;
struct TYPE_5__ {int test_active; TYPE_1__ test_data; } ;
struct TYPE_6__ {int i2c_defer_count; scalar_t__ i2c_nack_count; } ;
struct intel_dp {TYPE_2__ compliance; TYPE_3__ aux; struct intel_connector* attached_connector; } ;
struct drm_connector {scalar_t__ edid_corrupt; } ;
struct intel_connector {struct edid* detect_edid; struct drm_connector base; } ;
struct edid {int /*<<< orphan*/  checksum; int /*<<< orphan*/  extensions; } ;

/* Variables and functions */
 int DP_TEST_ACK ; 
 int /*<<< orphan*/  DP_TEST_EDID_CHECKSUM ; 
 int DP_TEST_EDID_CHECKSUM_WRITE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  INTEL_DP_RESOLUTION_FAILSAFE ; 
 int /*<<< orphan*/  INTEL_DP_RESOLUTION_PREFERRED ; 
 scalar_t__ drm_dp_dpcd_writeb (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 intel_dp_autotest_edid(struct intel_dp *intel_dp)
{
	u8 test_result = DP_TEST_ACK;
	struct intel_connector *intel_connector = intel_dp->attached_connector;
	struct drm_connector *connector = &intel_connector->base;

	if (intel_connector->detect_edid == NULL ||
	    connector->edid_corrupt ||
	    intel_dp->aux.i2c_defer_count > 6) {
		/* Check EDID read for NACKs, DEFERs and corruption
		 * (DP CTS 1.2 Core r1.1)
		 *    4.2.2.4 : Failed EDID read, I2C_NAK
		 *    4.2.2.5 : Failed EDID read, I2C_DEFER
		 *    4.2.2.6 : EDID corruption detected
		 * Use failsafe mode for all cases
		 */
		if (intel_dp->aux.i2c_nack_count > 0 ||
			intel_dp->aux.i2c_defer_count > 0)
			DRM_DEBUG_KMS("EDID read had %d NACKs, %d DEFERs\n",
				      intel_dp->aux.i2c_nack_count,
				      intel_dp->aux.i2c_defer_count);
		intel_dp->compliance.test_data.edid = INTEL_DP_RESOLUTION_FAILSAFE;
	} else {
		struct edid *block = intel_connector->detect_edid;

		/* We have to write the checksum
		 * of the last block read
		 */
		block += intel_connector->detect_edid->extensions;

		if (drm_dp_dpcd_writeb(&intel_dp->aux, DP_TEST_EDID_CHECKSUM,
				       block->checksum) <= 0)
			DRM_DEBUG_KMS("Failed to write EDID checksum\n");

		test_result = DP_TEST_ACK | DP_TEST_EDID_CHECKSUM_WRITE;
		intel_dp->compliance.test_data.edid = INTEL_DP_RESOLUTION_PREFERRED;
	}

	/* Set test active flag here so userspace doesn't interrupt things */
	intel_dp->compliance.test_active = 1;

	return test_result;
}