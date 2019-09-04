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
struct TYPE_2__ {int /*<<< orphan*/  child_dev_num; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
 int I915_MAX_PORTS ; 
 int /*<<< orphan*/  IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int PORT_A ; 
 int /*<<< orphan*/  parse_ddi_port (struct drm_i915_private*,int,int) ; 

__attribute__((used)) static void parse_ddi_ports(struct drm_i915_private *dev_priv, u8 bdb_version)
{
	enum port port;

	if (!HAS_DDI(dev_priv) && !IS_CHERRYVIEW(dev_priv))
		return;

	if (!dev_priv->vbt.child_dev_num)
		return;

	if (bdb_version < 155)
		return;

	for (port = PORT_A; port < I915_MAX_PORTS; port++)
		parse_ddi_port(dev_priv, port, bdb_version);
}