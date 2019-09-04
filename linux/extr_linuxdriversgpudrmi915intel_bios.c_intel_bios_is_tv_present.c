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
struct TYPE_2__ {int child_dev_num; struct child_device_config* child_dev; int /*<<< orphan*/  int_tv_support; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct child_device_config {int device_type; scalar_t__ addin_offset; } ;

/* Variables and functions */
#define  DEVICE_TYPE_INT_TV 130 
#define  DEVICE_TYPE_TV 129 
#define  DEVICE_TYPE_TV_SVIDEO_COMPOSITE 128 

bool intel_bios_is_tv_present(struct drm_i915_private *dev_priv)
{
	const struct child_device_config *child;
	int i;

	if (!dev_priv->vbt.int_tv_support)
		return false;

	if (!dev_priv->vbt.child_dev_num)
		return true;

	for (i = 0; i < dev_priv->vbt.child_dev_num; i++) {
		child = dev_priv->vbt.child_dev + i;
		/*
		 * If the device type is not TV, continue.
		 */
		switch (child->device_type) {
		case DEVICE_TYPE_INT_TV:
		case DEVICE_TYPE_TV:
		case DEVICE_TYPE_TV_SVIDEO_COMPOSITE:
			break;
		default:
			continue;
		}
		/* Only when the addin_offset is non-zero, it is regarded
		 * as present.
		 */
		if (child->addin_offset)
			return true;
	}

	return false;
}