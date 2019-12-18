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
typedef  int /*<<< orphan*/  u32 ;
struct intel_digital_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int /*<<< orphan*/  DRM_HDCP_DDC_V_PRIME (int) ; 
 int DRM_HDCP_V_PRIME_NUM_PARTS ; 
 int /*<<< orphan*/  DRM_HDCP_V_PRIME_PART_LEN ; 
 int EINVAL ; 
 int intel_hdmi_hdcp_read (struct intel_digital_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int intel_hdmi_hdcp_read_v_prime_part(struct intel_digital_port *intel_dig_port,
				      int i, u32 *part)
{
	int ret;

	if (i >= DRM_HDCP_V_PRIME_NUM_PARTS)
		return -EINVAL;

	ret = intel_hdmi_hdcp_read(intel_dig_port, DRM_HDCP_DDC_V_PRIME(i),
				   part, DRM_HDCP_V_PRIME_PART_LEN);
	if (ret)
		DRM_DEBUG_KMS("Read V'[%d] over DDC failed (%d)\n", i, ret);
	return ret;
}