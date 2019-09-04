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
struct drm_gem_object {int dummy; } ;
struct bochs_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bochs_bo_unref (struct bochs_bo**) ; 
 struct bochs_bo* gem_to_bochs_bo (struct drm_gem_object*) ; 

void bochs_gem_free_object(struct drm_gem_object *obj)
{
	struct bochs_bo *bochs_bo = gem_to_bochs_bo(obj);

	bochs_bo_unref(&bochs_bo);
}