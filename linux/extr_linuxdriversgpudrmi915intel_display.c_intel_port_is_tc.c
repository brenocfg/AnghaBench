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
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 int PORT_C ; 
 int PORT_F ; 

bool intel_port_is_tc(struct drm_i915_private *dev_priv, enum port port)
{
	if (IS_ICELAKE(dev_priv))
		return port >= PORT_C && port <= PORT_F;

	return false;
}