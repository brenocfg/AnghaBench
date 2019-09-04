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
typedef  int /*<<< orphan*/  u32 ;
struct i915_gem_context {int dummy; } ;
struct drm_i915_file_private {int /*<<< orphan*/  context_idr; } ;

/* Variables and functions */
 struct i915_gem_context* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct i915_gem_context *
__i915_gem_context_lookup_rcu(struct drm_i915_file_private *file_priv, u32 id)
{
	return idr_find(&file_priv->context_idr, id);
}