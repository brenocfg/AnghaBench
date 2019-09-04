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
struct ib_uverbs_file {int /*<<< orphan*/  hw_destroy_rwsem; } ;
struct ib_uobject {int /*<<< orphan*/  usecnt; struct ib_uverbs_file* ufile; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_REMOVE_DESTROY ; 
 int /*<<< orphan*/  UVERBS_LOOKUP_WRITE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int uverbs_destroy_uobject (struct ib_uobject*,int /*<<< orphan*/ ) ; 
 int uverbs_try_lock_object (struct ib_uobject*,int /*<<< orphan*/ ) ; 

int uobj_destroy(struct ib_uobject *uobj)
{
	struct ib_uverbs_file *ufile = uobj->ufile;
	int ret;

	down_read(&ufile->hw_destroy_rwsem);

	ret = uverbs_try_lock_object(uobj, UVERBS_LOOKUP_WRITE);
	if (ret)
		goto out_unlock;

	ret = uverbs_destroy_uobject(uobj, RDMA_REMOVE_DESTROY);
	if (ret) {
		atomic_set(&uobj->usecnt, 0);
		goto out_unlock;
	}

out_unlock:
	up_read(&ufile->hw_destroy_rwsem);
	return ret;
}