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
struct ib_uobject {int /*<<< orphan*/  usecnt; } ;
typedef  enum rdma_lookup_mode { ____Placeholder_rdma_lookup_mode } rdma_lookup_mode ;

/* Variables and functions */
 int EBUSY ; 
#define  UVERBS_LOOKUP_DESTROY 130 
#define  UVERBS_LOOKUP_READ 129 
#define  UVERBS_LOOKUP_WRITE 128 
 int /*<<< orphan*/  atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int atomic_fetch_add_unless (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int uverbs_try_lock_object(struct ib_uobject *uobj,
				  enum rdma_lookup_mode mode)
{
	/*
	 * When a shared access is required, we use a positive counter. Each
	 * shared access request checks that the value != -1 and increment it.
	 * Exclusive access is required for operations like write or destroy.
	 * In exclusive access mode, we check that the counter is zero (nobody
	 * claimed this object) and we set it to -1. Releasing a shared access
	 * lock is done simply by decreasing the counter. As for exclusive
	 * access locks, since only a single one of them is is allowed
	 * concurrently, setting the counter to zero is enough for releasing
	 * this lock.
	 */
	switch (mode) {
	case UVERBS_LOOKUP_READ:
		return atomic_fetch_add_unless(&uobj->usecnt, 1, -1) == -1 ?
			-EBUSY : 0;
	case UVERBS_LOOKUP_WRITE:
		/* lock is exclusive */
		return atomic_cmpxchg(&uobj->usecnt, 0, -1) == 0 ? 0 : -EBUSY;
	case UVERBS_LOOKUP_DESTROY:
		return 0;
	}
	return 0;
}