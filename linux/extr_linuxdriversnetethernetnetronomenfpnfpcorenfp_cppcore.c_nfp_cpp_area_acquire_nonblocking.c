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
struct nfp_cpp_area {int /*<<< orphan*/  mutex; int /*<<< orphan*/  refcount; TYPE_2__* cpp; } ;
struct TYPE_4__ {TYPE_1__* op; } ;
struct TYPE_3__ {int (* area_acquire ) (struct nfp_cpp_area*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_cpp_area_get (struct nfp_cpp_area*) ; 
 int stub1 (struct nfp_cpp_area*) ; 

int nfp_cpp_area_acquire_nonblocking(struct nfp_cpp_area *area)
{
	mutex_lock(&area->mutex);
	if (atomic_inc_return(&area->refcount) == 1) {
		if (area->cpp->op->area_acquire) {
			int err;

			err = area->cpp->op->area_acquire(area);
			if (err < 0) {
				atomic_dec(&area->refcount);
				mutex_unlock(&area->mutex);
				return err;
			}
		}
	}
	mutex_unlock(&area->mutex);

	nfp_cpp_area_get(area);
	return 0;
}