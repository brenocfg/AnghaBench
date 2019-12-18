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
struct drm_i915_file_private {int dummy; } ;
struct drm_file {struct drm_i915_file_private* driver_priv; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_context_close (struct drm_file*) ; 
 int /*<<< orphan*/  i915_gem_flush_free_objects (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_release (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  kfree (struct drm_i915_file_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_i915 (struct drm_device*) ; 

__attribute__((used)) static void i915_driver_postclose(struct drm_device *dev, struct drm_file *file)
{
	struct drm_i915_file_private *file_priv = file->driver_priv;

	mutex_lock(&dev->struct_mutex);
	i915_gem_context_close(file);
	i915_gem_release(dev, file);
	mutex_unlock(&dev->struct_mutex);

	kfree(file_priv);

	/* Catch up with all the deferred frees from "this" client */
	i915_gem_flush_free_objects(to_i915(dev));
}