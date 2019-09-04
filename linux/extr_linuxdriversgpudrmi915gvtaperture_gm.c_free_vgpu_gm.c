#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  high_gm_node; int /*<<< orphan*/  low_gm_node; } ;
struct intel_vgpu {TYPE_2__ gm; TYPE_1__* gvt; } ;
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_3__ drm; } ;
struct TYPE_4__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_vgpu_gm(struct intel_vgpu *vgpu)
{
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;

	mutex_lock(&dev_priv->drm.struct_mutex);
	drm_mm_remove_node(&vgpu->gm.low_gm_node);
	drm_mm_remove_node(&vgpu->gm.high_gm_node);
	mutex_unlock(&dev_priv->drm.struct_mutex);
}