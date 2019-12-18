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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  aux; } ;
struct intel_digital_port {TYPE_1__ dp; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_AUX_HDCP_V_PRIME (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int DRM_HDCP_V_PRIME_NUM_PARTS ; 
 int DRM_HDCP_V_PRIME_PART_LEN ; 
 int EINVAL ; 
 int EIO ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
int intel_dp_hdcp_read_v_prime_part(struct intel_digital_port *intel_dig_port,
				    int i, u32 *part)
{
	ssize_t ret;

	if (i >= DRM_HDCP_V_PRIME_NUM_PARTS)
		return -EINVAL;

	ret = drm_dp_dpcd_read(&intel_dig_port->dp.aux,
			       DP_AUX_HDCP_V_PRIME(i), part,
			       DRM_HDCP_V_PRIME_PART_LEN);
	if (ret != DRM_HDCP_V_PRIME_PART_LEN) {
		DRM_DEBUG_KMS("Read v'[%d] from DP/AUX failed (%zd)\n", i, ret);
		return ret >= 0 ? -EIO : ret;
	}
	return 0;
}