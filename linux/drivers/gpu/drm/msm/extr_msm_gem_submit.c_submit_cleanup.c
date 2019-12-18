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
struct msm_gem_submit {unsigned int nr_bos; int /*<<< orphan*/  ticket; TYPE_1__* bos; } ;
struct msm_gem_object {int /*<<< orphan*/  base; int /*<<< orphan*/  submit_entry; } ;
struct TYPE_2__ {struct msm_gem_object* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_unlock_unpin_bo (struct msm_gem_submit*,unsigned int,int) ; 
 int /*<<< orphan*/  ww_acquire_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void submit_cleanup(struct msm_gem_submit *submit)
{
	unsigned i;

	for (i = 0; i < submit->nr_bos; i++) {
		struct msm_gem_object *msm_obj = submit->bos[i].obj;
		submit_unlock_unpin_bo(submit, i, false);
		list_del_init(&msm_obj->submit_entry);
		drm_gem_object_put(&msm_obj->base);
	}

	ww_acquire_fini(&submit->ticket);
}