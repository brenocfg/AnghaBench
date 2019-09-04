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
struct TYPE_2__ {int child_dev_num; struct child_device_config* child_dev; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct child_device_config {int device_type; int dvo_port; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int DEVICE_TYPE_MIPI_OUTPUT ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
#define  DVO_PORT_MIPIA 131 
#define  DVO_PORT_MIPIB 130 
#define  DVO_PORT_MIPIC 129 
#define  DVO_PORT_MIPID 128 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 

bool intel_bios_is_dsi_present(struct drm_i915_private *dev_priv,
			       enum port *port)
{
	const struct child_device_config *child;
	u8 dvo_port;
	int i;

	for (i = 0; i < dev_priv->vbt.child_dev_num; i++) {
		child = dev_priv->vbt.child_dev + i;

		if (!(child->device_type & DEVICE_TYPE_MIPI_OUTPUT))
			continue;

		dvo_port = child->dvo_port;

		switch (dvo_port) {
		case DVO_PORT_MIPIA:
		case DVO_PORT_MIPIC:
			if (port)
				*port = dvo_port - DVO_PORT_MIPIA;
			return true;
		case DVO_PORT_MIPIB:
		case DVO_PORT_MIPID:
			DRM_DEBUG_KMS("VBT has unsupported DSI port %c\n",
				      port_name(dvo_port - DVO_PORT_MIPIA));
			break;
		}
	}

	return false;
}