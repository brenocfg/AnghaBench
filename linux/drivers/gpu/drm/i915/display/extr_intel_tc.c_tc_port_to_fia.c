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
typedef  enum tc_port { ____Placeholder_tc_port } tc_port ;
typedef  enum phy_fia { ____Placeholder_phy_fia } phy_fia ;

/* Variables and functions */
 int FIA1 ; 
 int /*<<< orphan*/  has_modular_fia (struct drm_i915_private*) ; 

__attribute__((used)) static enum phy_fia tc_port_to_fia(struct drm_i915_private *i915,
				   enum tc_port tc_port)
{
	if (!has_modular_fia(i915))
		return FIA1;

	/*
	 * Each Modular FIA instance houses 2 TC ports. In SOC that has more
	 * than two TC ports, there are multiple instances of Modular FIA.
	 */
	return tc_port / 2;
}