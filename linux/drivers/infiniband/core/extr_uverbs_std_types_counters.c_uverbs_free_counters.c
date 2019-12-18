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
struct ib_uobject {struct ib_counters* object; } ;
struct ib_counters {TYPE_2__* device; int /*<<< orphan*/  usecnt; } ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;
struct TYPE_3__ {int (* destroy_counters ) (struct ib_counters*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int ib_destroy_usecnt (int /*<<< orphan*/ *,int,struct ib_uobject*) ; 
 int stub1 (struct ib_counters*) ; 

__attribute__((used)) static int uverbs_free_counters(struct ib_uobject *uobject,
				enum rdma_remove_reason why,
				struct uverbs_attr_bundle *attrs)
{
	struct ib_counters *counters = uobject->object;
	int ret;

	ret = ib_destroy_usecnt(&counters->usecnt, why, uobject);
	if (ret)
		return ret;

	return counters->device->ops.destroy_counters(counters);
}