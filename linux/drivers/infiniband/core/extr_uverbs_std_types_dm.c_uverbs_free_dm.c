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
struct uverbs_attr_bundle {int dummy; } ;
struct ib_uobject {struct ib_dm* object; } ;
struct ib_dm {TYPE_2__* device; int /*<<< orphan*/  usecnt; } ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;
struct TYPE_3__ {int (* dealloc_dm ) (struct ib_dm*,struct uverbs_attr_bundle*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int ib_destroy_usecnt (int /*<<< orphan*/ *,int,struct ib_uobject*) ; 
 int stub1 (struct ib_dm*,struct uverbs_attr_bundle*) ; 

__attribute__((used)) static int uverbs_free_dm(struct ib_uobject *uobject,
			  enum rdma_remove_reason why,
			  struct uverbs_attr_bundle *attrs)
{
	struct ib_dm *dm = uobject->object;
	int ret;

	ret = ib_destroy_usecnt(&dm->usecnt, why, uobject);
	if (ret)
		return ret;

	return dm->device->ops.dealloc_dm(dm, attrs);
}