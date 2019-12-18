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
struct rdma_ah_attr {scalar_t__ type; } ;
struct ib_udata {int dummy; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_AH_GRH ; 
 scalar_t__ RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  create_ib_ah (struct ib_ah*,struct rdma_ah_attr*) ; 
 int create_iboe_ah (struct ib_ah*,struct rdma_ah_attr*) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 

int mlx4_ib_create_ah(struct ib_ah *ib_ah, struct rdma_ah_attr *ah_attr,
		      u32 flags, struct ib_udata *udata)

{
	if (ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE) {
		if (!(rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH))
			return -EINVAL;
		/*
		 * TBD: need to handle the case when we get
		 * called in an atomic context and there we
		 * might sleep.  We don't expect this
		 * currently since we're working with link
		 * local addresses which we can translate
		 * without going to sleep.
		 */
		return create_iboe_ah(ib_ah, ah_attr);
	}

	create_ib_ah(ib_ah, ah_attr);
	return 0;
}