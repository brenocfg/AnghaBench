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
#define  UVERBS_LOOKUP_DESTROY 130 
#define  UVERBS_LOOKUP_READ 129 
#define  UVERBS_LOOKUP_WRITE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void assert_uverbs_usecnt(struct ib_uobject *uobj,
				 enum rdma_lookup_mode mode)
{
#ifdef CONFIG_LOCKDEP
	switch (mode) {
	case UVERBS_LOOKUP_READ:
		WARN_ON(atomic_read(&uobj->usecnt) <= 0);
		break;
	case UVERBS_LOOKUP_WRITE:
		WARN_ON(atomic_read(&uobj->usecnt) != -1);
		break;
	case UVERBS_LOOKUP_DESTROY:
		break;
	}
#endif
}