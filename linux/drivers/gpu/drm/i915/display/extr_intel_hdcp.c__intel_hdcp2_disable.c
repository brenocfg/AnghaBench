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
struct TYPE_6__ {int hdcp2_encrypted; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ base; int /*<<< orphan*/  name; } ;
struct intel_connector {TYPE_3__ hdcp; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 scalar_t__ hdcp2_deauthenticate_port (struct intel_connector*) ; 
 int hdcp2_disable_encryption (struct intel_connector*) ; 

__attribute__((used)) static int _intel_hdcp2_disable(struct intel_connector *connector)
{
	int ret;

	DRM_DEBUG_KMS("[%s:%d] HDCP2.2 is being Disabled\n",
		      connector->base.name, connector->base.base.id);

	ret = hdcp2_disable_encryption(connector);

	if (hdcp2_deauthenticate_port(connector) < 0)
		DRM_DEBUG_KMS("Port deauth failed.\n");

	connector->hdcp.hdcp2_encrypted = false;

	return ret;
}