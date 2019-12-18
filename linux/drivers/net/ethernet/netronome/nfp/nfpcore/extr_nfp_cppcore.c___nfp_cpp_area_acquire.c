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
struct nfp_cpp_area {int /*<<< orphan*/  refcount; TYPE_2__* cpp; } ;
struct TYPE_4__ {int /*<<< orphan*/  waitq; TYPE_1__* op; } ;
struct TYPE_3__ {int /*<<< orphan*/  area_acquire; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_cpp_area_acquire_try (struct nfp_cpp_area*,int*) ; 
 int /*<<< orphan*/  nfp_cpp_area_get (struct nfp_cpp_area*) ; 
 int /*<<< orphan*/  nfp_warn (TYPE_2__*,char*,int) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __nfp_cpp_area_acquire(struct nfp_cpp_area *area)
{
	int err, status;

	if (atomic_inc_return(&area->refcount) > 1)
		return 0;

	if (!area->cpp->op->area_acquire)
		return 0;

	err = wait_event_interruptible(area->cpp->waitq,
				       nfp_cpp_area_acquire_try(area, &status));
	if (!err)
		err = status;
	if (err) {
		nfp_warn(area->cpp, "Warning: area wait failed: %d\n", err);
		atomic_dec(&area->refcount);
		return err;
	}

	nfp_cpp_area_get(area);

	return 0;
}