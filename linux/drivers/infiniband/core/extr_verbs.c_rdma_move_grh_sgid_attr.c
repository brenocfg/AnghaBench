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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct ib_gid_attr const* sgid_attr; } ;
struct rdma_ah_attr {TYPE_1__ grh; } ;
struct ib_gid_attr {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdma_ah_set_grh (struct rdma_ah_attr*,union ib_gid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rdma_move_grh_sgid_attr(struct rdma_ah_attr *attr, union ib_gid *dgid,
			     u32 flow_label, u8 hop_limit, u8 traffic_class,
			     const struct ib_gid_attr *sgid_attr)
{
	rdma_ah_set_grh(attr, dgid, flow_label, sgid_attr->index, hop_limit,
			traffic_class);
	attr->grh.sgid_attr = sgid_attr;
}