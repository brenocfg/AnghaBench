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
struct intel_hdcp_shim {int dummy; } ;
struct intel_hdcp {int hdcp2_supported; } ;
struct intel_connector {struct intel_hdcp hdcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int initialize_hdcp_port_data (struct intel_connector*,struct intel_hdcp_shim const*) ; 

__attribute__((used)) static void intel_hdcp2_init(struct intel_connector *connector,
			     const struct intel_hdcp_shim *shim)
{
	struct intel_hdcp *hdcp = &connector->hdcp;
	int ret;

	ret = initialize_hdcp_port_data(connector, shim);
	if (ret) {
		DRM_DEBUG_KMS("Mei hdcp data init failed\n");
		return;
	}

	hdcp->hdcp2_supported = true;
}