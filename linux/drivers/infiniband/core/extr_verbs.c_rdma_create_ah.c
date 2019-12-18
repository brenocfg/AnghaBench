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
typedef  int /*<<< orphan*/  u32 ;
struct rdma_ah_attr {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct ib_gid_attr {int dummy; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 struct ib_ah* ERR_PTR (int) ; 
 struct ib_ah* _rdma_create_ah (struct ib_pd*,struct rdma_ah_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rdma_fill_sgid_attr (int /*<<< orphan*/ ,struct rdma_ah_attr*,struct ib_gid_attr const**) ; 
 int /*<<< orphan*/  rdma_unfill_sgid_attr (struct rdma_ah_attr*,struct ib_gid_attr const*) ; 

struct ib_ah *rdma_create_ah(struct ib_pd *pd, struct rdma_ah_attr *ah_attr,
			     u32 flags)
{
	const struct ib_gid_attr *old_sgid_attr;
	struct ib_ah *ah;
	int ret;

	ret = rdma_fill_sgid_attr(pd->device, ah_attr, &old_sgid_attr);
	if (ret)
		return ERR_PTR(ret);

	ah = _rdma_create_ah(pd, ah_attr, flags, NULL);

	rdma_unfill_sgid_attr(ah_attr, old_sgid_attr);
	return ah;
}