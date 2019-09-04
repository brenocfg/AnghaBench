#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct etnaviv_gem_submit {TYPE_2__* bos; } ;
struct etnaviv_gem_object {TYPE_1__* resv; } ;
struct TYPE_4__ {int flags; struct etnaviv_gem_object* obj; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BO_LOCKED ; 
 int /*<<< orphan*/  ww_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void submit_unlock_object(struct etnaviv_gem_submit *submit, int i)
{
	if (submit->bos[i].flags & BO_LOCKED) {
		struct etnaviv_gem_object *etnaviv_obj = submit->bos[i].obj;

		ww_mutex_unlock(&etnaviv_obj->resv->lock);
		submit->bos[i].flags &= ~BO_LOCKED;
	}
}