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
struct drm_i915_gem_object {TYPE_1__* stolen; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */

__attribute__((used)) static int obj_rank_by_stolen(const void *A, const void *B)
{
	const struct drm_i915_gem_object *a =
		*(const struct drm_i915_gem_object **)A;
	const struct drm_i915_gem_object *b =
		*(const struct drm_i915_gem_object **)B;

	if (a->stolen->start < b->stolen->start)
		return -1;
	if (a->stolen->start > b->stolen->start)
		return 1;
	return 0;
}