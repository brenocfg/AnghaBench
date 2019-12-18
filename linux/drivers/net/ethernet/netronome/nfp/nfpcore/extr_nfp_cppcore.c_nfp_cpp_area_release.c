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
struct nfp_cpp_area {int /*<<< orphan*/  mutex; TYPE_2__* cpp; int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {int /*<<< orphan*/  waitq; TYPE_1__* op; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* area_release ) (struct nfp_cpp_area*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_cpp_area_put (struct nfp_cpp_area*) ; 
 int /*<<< orphan*/  stub1 (struct nfp_cpp_area*) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

void nfp_cpp_area_release(struct nfp_cpp_area *area)
{
	mutex_lock(&area->mutex);
	/* Only call the release on refcount == 0 */
	if (atomic_dec_and_test(&area->refcount)) {
		if (area->cpp->op->area_release) {
			area->cpp->op->area_release(area);
			/* Let anyone waiting for a BAR try to get one.. */
			wake_up_interruptible_all(&area->cpp->waitq);
		}
	}
	mutex_unlock(&area->mutex);

	nfp_cpp_area_put(area);
}