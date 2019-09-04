#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int child_dev_num; struct child_device_config* child_dev; TYPE_1__* ddi_port_info; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct child_device_config {short const dvo_port; int device_type; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_3__ {int supports_edp; } ;

/* Variables and functions */
 int DEVICE_TYPE_eDP ; 
 int DEVICE_TYPE_eDP_BITS ; 
#define  DVO_PORT_DPB 137 
#define  DVO_PORT_DPC 136 
#define  DVO_PORT_DPD 135 
#define  DVO_PORT_DPE 134 
#define  DVO_PORT_DPF 133 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
#define  PORT_B 132 
#define  PORT_C 131 
#define  PORT_D 130 
#define  PORT_E 129 
#define  PORT_F 128 

bool intel_bios_is_port_edp(struct drm_i915_private *dev_priv, enum port port)
{
	const struct child_device_config *child;
	static const short port_mapping[] = {
		[PORT_B] = DVO_PORT_DPB,
		[PORT_C] = DVO_PORT_DPC,
		[PORT_D] = DVO_PORT_DPD,
		[PORT_E] = DVO_PORT_DPE,
		[PORT_F] = DVO_PORT_DPF,
	};
	int i;

	if (HAS_DDI(dev_priv))
		return dev_priv->vbt.ddi_port_info[port].supports_edp;

	if (!dev_priv->vbt.child_dev_num)
		return false;

	for (i = 0; i < dev_priv->vbt.child_dev_num; i++) {
		child = dev_priv->vbt.child_dev + i;

		if (child->dvo_port == port_mapping[port] &&
		    (child->device_type & DEVICE_TYPE_eDP_BITS) ==
		    (DEVICE_TYPE_eDP & DEVICE_TYPE_eDP_BITS))
			return true;
	}

	return false;
}