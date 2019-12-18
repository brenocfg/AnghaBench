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
struct drm_psb_private {int child_dev_num; struct child_device_config* child_dev; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct child_device_config {scalar_t__ dvo_port; scalar_t__ device_type; } ;

/* Variables and functions */
 scalar_t__ DEVICE_TYPE_eDP ; 
 scalar_t__ PORT_IDPC ; 

__attribute__((used)) static bool cdv_intel_dpc_is_edp(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct child_device_config *p_child;
	int i;

	if (!dev_priv->child_dev_num)
		return false;

	for (i = 0; i < dev_priv->child_dev_num; i++) {
		p_child = dev_priv->child_dev + i;

		if (p_child->dvo_port == PORT_IDPC &&
		    p_child->device_type == DEVICE_TYPE_eDP)
			return true;
	}
	return false;
}