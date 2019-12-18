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
struct rdma_ah_attr {int dummy; } ;
struct ib_ah {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dgid; int /*<<< orphan*/  tclass; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  gid_index; int /*<<< orphan*/  flowlabel; int /*<<< orphan*/  stat_rate; int /*<<< orphan*/  port; int /*<<< orphan*/  sl; } ;
struct hns_roce_ah {TYPE_1__ av; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct rdma_ah_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ah_set_dgid_raw (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_grh (struct rdma_ah_attr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_static_rate (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 struct hns_roce_ah* to_hr_ah (struct ib_ah*) ; 

int hns_roce_query_ah(struct ib_ah *ibah, struct rdma_ah_attr *ah_attr)
{
	struct hns_roce_ah *ah = to_hr_ah(ibah);

	memset(ah_attr, 0, sizeof(*ah_attr));

	rdma_ah_set_sl(ah_attr, ah->av.sl);
	rdma_ah_set_port_num(ah_attr, ah->av.port);
	rdma_ah_set_static_rate(ah_attr, ah->av.stat_rate);
	rdma_ah_set_grh(ah_attr, NULL, ah->av.flowlabel,
			ah->av.gid_index, ah->av.hop_limit, ah->av.tclass);
	rdma_ah_set_dgid_raw(ah_attr, ah->av.dgid);

	return 0;
}