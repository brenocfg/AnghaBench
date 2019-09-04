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
struct ib_uobject {struct ib_dm* object; } ;
struct ib_dm {TYPE_1__* device; int /*<<< orphan*/  usecnt; } ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;
struct TYPE_2__ {int (* dealloc_dm ) (struct ib_dm*) ;} ;

/* Variables and functions */
 int ib_destroy_usecnt (int /*<<< orphan*/ *,int,struct ib_uobject*) ; 
 int stub1 (struct ib_dm*) ; 

__attribute__((used)) static int uverbs_free_dm(struct ib_uobject *uobject,
			  enum rdma_remove_reason why)
{
	struct ib_dm *dm = uobject->object;
	int ret;

	ret = ib_destroy_usecnt(&dm->usecnt, why, uobject);
	if (ret)
		return ret;

	return dm->device->dealloc_dm(dm);
}