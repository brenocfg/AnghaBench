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
struct uverbs_attr_bundle {int dummy; } ;
struct mlx5_ib_flow_matcher {int /*<<< orphan*/  usecnt; } ;
struct ib_uobject {struct mlx5_ib_flow_matcher* object; } ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;

/* Variables and functions */
 int ib_destroy_usecnt (int /*<<< orphan*/ *,int,struct ib_uobject*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_flow_matcher*) ; 

__attribute__((used)) static int flow_matcher_cleanup(struct ib_uobject *uobject,
				enum rdma_remove_reason why,
				struct uverbs_attr_bundle *attrs)
{
	struct mlx5_ib_flow_matcher *obj = uobject->object;
	int ret;

	ret = ib_destroy_usecnt(&obj->usecnt, why, uobject);
	if (ret)
		return ret;

	kfree(obj);
	return 0;
}