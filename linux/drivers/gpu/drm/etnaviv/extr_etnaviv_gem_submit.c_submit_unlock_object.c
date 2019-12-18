#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct etnaviv_gem_submit {TYPE_3__* bos; } ;
struct drm_gem_object {TYPE_2__* resv; } ;
struct TYPE_6__ {int flags; TYPE_1__* obj; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {struct drm_gem_object base; } ;

/* Variables and functions */
 int BO_LOCKED ; 
 int /*<<< orphan*/  ww_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void submit_unlock_object(struct etnaviv_gem_submit *submit, int i)
{
	if (submit->bos[i].flags & BO_LOCKED) {
		struct drm_gem_object *obj = &submit->bos[i].obj->base;

		ww_mutex_unlock(&obj->resv->lock);
		submit->bos[i].flags &= ~BO_LOCKED;
	}
}