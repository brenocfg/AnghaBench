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
struct child_device_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  parse_ddi_port (struct drm_i915_private*,struct child_device_config const*,int) ; 

__attribute__((used)) static void parse_ddi_ports(struct drm_i915_private *dev_priv, u8 bdb_version)
{
	const struct child_device_config *child;
	int i;

	if (!HAS_DDI(dev_priv) && !IS_CHERRYVIEW(dev_priv))
		return;

	if (bdb_version < 155)
		return;

	for (i = 0; i < dev_priv->vbt.child_dev_num; i++) {
		child = dev_priv->vbt.child_dev + i;

		parse_ddi_port(dev_priv, child, bdb_version);
	}
}