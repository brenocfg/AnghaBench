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
struct drm_i915_file_private {int /*<<< orphan*/  vm_idr_lock; int /*<<< orphan*/  vm_idr; int /*<<< orphan*/  context_idr_lock; int /*<<< orphan*/  context_idr; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  context_idr_cleanup ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_idr_cleanup ; 

void i915_gem_context_close(struct drm_file *file)
{
	struct drm_i915_file_private *file_priv = file->driver_priv;

	idr_for_each(&file_priv->context_idr, context_idr_cleanup, NULL);
	idr_destroy(&file_priv->context_idr);
	mutex_destroy(&file_priv->context_idr_lock);

	idr_for_each(&file_priv->vm_idr, vm_idr_cleanup, NULL);
	idr_destroy(&file_priv->vm_idr);
	mutex_destroy(&file_priv->vm_idr_lock);
}