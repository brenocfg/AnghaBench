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
struct ib_uobject {struct ib_flow_action* object; } ;
struct ib_flow_action {TYPE_1__* device; int /*<<< orphan*/  usecnt; } ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;
struct TYPE_2__ {int (* destroy_flow_action ) (struct ib_flow_action*) ;} ;

/* Variables and functions */
 int ib_destroy_usecnt (int /*<<< orphan*/ *,int,struct ib_uobject*) ; 
 int stub1 (struct ib_flow_action*) ; 

__attribute__((used)) static int uverbs_free_flow_action(struct ib_uobject *uobject,
				   enum rdma_remove_reason why)
{
	struct ib_flow_action *action = uobject->object;
	int ret;

	ret = ib_destroy_usecnt(&action->usecnt, why, uobject);
	if (ret)
		return ret;

	return action->device->destroy_flow_action(action);
}