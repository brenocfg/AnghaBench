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
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 scalar_t__ IS_ELKHARTLAKE (struct drm_i915_private*) ; 
 int PHY_A ; 
 int PORT_D ; 

enum phy intel_port_to_phy(struct drm_i915_private *i915, enum port port)
{
	if (IS_ELKHARTLAKE(i915) && port == PORT_D)
		return PHY_A;

	return (enum phy)port;
}