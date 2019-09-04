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
struct qxl_bo {int /*<<< orphan*/  gem_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_get (int /*<<< orphan*/ *) ; 

struct qxl_bo *qxl_bo_ref(struct qxl_bo *bo)
{
	drm_gem_object_get(&bo->gem_base);
	return bo;
}