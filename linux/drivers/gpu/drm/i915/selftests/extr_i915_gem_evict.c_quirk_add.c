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
struct list_head {int dummy; } ;
struct TYPE_2__ {int quirked; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  st_link; TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void quirk_add(struct drm_i915_gem_object *obj,
		      struct list_head *objects)
{
	/* quirk is only for live tiled objects, use it to declare ownership */
	GEM_BUG_ON(obj->mm.quirked);
	obj->mm.quirked = true;
	list_add(&obj->st_link, objects);
}