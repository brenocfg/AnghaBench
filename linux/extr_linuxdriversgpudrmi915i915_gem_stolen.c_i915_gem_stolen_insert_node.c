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
typedef  int /*<<< orphan*/  u64 ;
struct drm_mm_node {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  U64_MAX ; 
 int i915_gem_stolen_insert_node_in_range (struct drm_i915_private*,struct drm_mm_node*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int i915_gem_stolen_insert_node(struct drm_i915_private *dev_priv,
				struct drm_mm_node *node, u64 size,
				unsigned alignment)
{
	return i915_gem_stolen_insert_node_in_range(dev_priv, node, size,
						    alignment, 0, U64_MAX);
}