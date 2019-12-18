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
struct qxl_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct qxl_bo* gem_to_qxl_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  qxl_bo_kunmap (struct qxl_bo*) ; 

void qxl_gem_prime_vunmap(struct drm_gem_object *obj, void *vaddr)
{
	struct qxl_bo *bo = gem_to_qxl_bo(obj);

	qxl_bo_kunmap(bo);
}