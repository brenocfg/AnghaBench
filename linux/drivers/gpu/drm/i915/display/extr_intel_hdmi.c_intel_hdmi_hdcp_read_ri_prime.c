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
typedef  int /*<<< orphan*/  u8 ;
struct intel_digital_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  DRM_HDCP_DDC_RI_PRIME ; 
 int /*<<< orphan*/  DRM_HDCP_RI_LEN ; 
 int intel_hdmi_hdcp_read (struct intel_digital_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int intel_hdmi_hdcp_read_ri_prime(struct intel_digital_port *intel_dig_port,
				  u8 *ri_prime)
{
	int ret;
	ret = intel_hdmi_hdcp_read(intel_dig_port, DRM_HDCP_DDC_RI_PRIME,
				   ri_prime, DRM_HDCP_RI_LEN);
	if (ret)
		DRM_DEBUG_KMS("Read Ri' over DDC failed (%d)\n", ret);
	return ret;
}