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
struct intel_digital_port {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,char*,int) ; 
 int intel_ddi_toggle_hdcp_signalling (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static
int intel_hdmi_hdcp_toggle_signalling(struct intel_digital_port *intel_dig_port,
				      bool enable)
{
	int ret;

	if (!enable)
		usleep_range(6, 60); /* Bspec says >= 6us */

	ret = intel_ddi_toggle_hdcp_signalling(&intel_dig_port->base, enable);
	if (ret) {
		DRM_ERROR("%s HDCP signalling failed (%d)\n",
			  enable ? "Enable" : "Disable", ret);
		return ret;
	}
	return 0;
}