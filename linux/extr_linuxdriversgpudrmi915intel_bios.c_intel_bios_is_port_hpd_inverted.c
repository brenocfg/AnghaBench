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
struct TYPE_2__ {int child_dev_num; struct child_device_config* child_dev; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct child_device_config {int dvo_port; int /*<<< orphan*/  hpd_invert; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
#define  DVO_PORT_DPA 133 
#define  DVO_PORT_DPB 132 
#define  DVO_PORT_DPC 131 
#define  DVO_PORT_HDMIA 130 
#define  DVO_PORT_HDMIB 129 
#define  DVO_PORT_HDMIC 128 
 int /*<<< orphan*/  IS_GEN9_LP (struct drm_i915_private*) ; 
 int PORT_A ; 
 int PORT_B ; 
 int PORT_C ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

bool
intel_bios_is_port_hpd_inverted(struct drm_i915_private *dev_priv,
				enum port port)
{
	const struct child_device_config *child;
	int i;

	if (WARN_ON_ONCE(!IS_GEN9_LP(dev_priv)))
		return false;

	for (i = 0; i < dev_priv->vbt.child_dev_num; i++) {
		child = dev_priv->vbt.child_dev + i;

		if (!child->hpd_invert)
			continue;

		switch (child->dvo_port) {
		case DVO_PORT_DPA:
		case DVO_PORT_HDMIA:
			if (port == PORT_A)
				return true;
			break;
		case DVO_PORT_DPB:
		case DVO_PORT_HDMIB:
			if (port == PORT_B)
				return true;
			break;
		case DVO_PORT_DPC:
		case DVO_PORT_HDMIC:
			if (port == PORT_C)
				return true;
			break;
		default:
			break;
		}
	}

	return false;
}