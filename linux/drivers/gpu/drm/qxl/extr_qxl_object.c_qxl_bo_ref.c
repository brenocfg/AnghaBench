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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct qxl_bo {TYPE_1__ tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_get (int /*<<< orphan*/ *) ; 

struct qxl_bo *qxl_bo_ref(struct qxl_bo *bo)
{
	drm_gem_object_get(&bo->tbo.base);
	return bo;
}