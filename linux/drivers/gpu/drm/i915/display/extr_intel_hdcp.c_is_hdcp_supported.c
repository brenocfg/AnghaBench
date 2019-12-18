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
 int INTEL_GEN (struct drm_i915_private*) ; 
 int PORT_E ; 

bool is_hdcp_supported(struct drm_i915_private *dev_priv, enum port port)
{
	/* PORT E doesn't have HDCP, and PORT F is disabled */
	return INTEL_GEN(dev_priv) >= 9 && port < PORT_E;
}