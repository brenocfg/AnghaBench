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
struct cirrus_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cirrus_bo_unref (struct cirrus_bo**) ; 
 struct cirrus_bo* gem_to_cirrus_bo (struct drm_gem_object*) ; 

void cirrus_gem_free_object(struct drm_gem_object *obj)
{
	struct cirrus_bo *cirrus_bo = gem_to_cirrus_bo(obj);

	cirrus_bo_unref(&cirrus_bo);
}