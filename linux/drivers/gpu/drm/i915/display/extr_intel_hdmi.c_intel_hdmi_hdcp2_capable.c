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
typedef  int u8 ;
struct intel_digital_port {int dummy; } ;
typedef  int /*<<< orphan*/  hdcp2_version ;

/* Variables and functions */
 int /*<<< orphan*/  HDCP_2_2_HDMI_REG_VER_OFFSET ; 
 int HDCP_2_2_HDMI_SUPPORT_MASK ; 
 int intel_hdmi_hdcp_read (struct intel_digital_port*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static
int intel_hdmi_hdcp2_capable(struct intel_digital_port *intel_dig_port,
			     bool *capable)
{
	u8 hdcp2_version;
	int ret;

	*capable = false;
	ret = intel_hdmi_hdcp_read(intel_dig_port, HDCP_2_2_HDMI_REG_VER_OFFSET,
				   &hdcp2_version, sizeof(hdcp2_version));
	if (!ret && hdcp2_version & HDCP_2_2_HDMI_SUPPORT_MASK)
		*capable = true;

	return ret;
}