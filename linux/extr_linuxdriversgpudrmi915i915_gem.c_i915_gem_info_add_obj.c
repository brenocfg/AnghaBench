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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  object_stat_lock; int /*<<< orphan*/  object_memory; int /*<<< orphan*/  object_count; } ;
struct drm_i915_private {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_gem_info_add_obj(struct drm_i915_private *dev_priv,
				  u64 size)
{
	spin_lock(&dev_priv->mm.object_stat_lock);
	dev_priv->mm.object_count++;
	dev_priv->mm.object_memory += size;
	spin_unlock(&dev_priv->mm.object_stat_lock);
}