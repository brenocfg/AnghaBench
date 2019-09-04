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
struct file {struct drm_file* private_data; } ;
struct drm_i915_private {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_release (int /*<<< orphan*/ *,struct file*) ; 

void mock_file_free(struct drm_i915_private *i915, struct drm_file *file)
{
	struct file filp = { .private_data = file };

	drm_release(NULL, &filp);
}