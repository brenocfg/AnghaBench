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
typedef  scalar_t__ u8 ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct mlx4_qp_path {int sched_queue; int grh_mylmc; int /*<<< orphan*/  rgid; int /*<<< orphan*/  tclass_flowlabel; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  mgid_index; scalar_t__ static_rate; int /*<<< orphan*/  rlid; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  ib_dev; struct mlx4_dev* dev; } ;
struct TYPE_2__ {scalar_t__ num_ports; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rdma_ah_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ah_find_type (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rdma_ah_set_dgid_raw (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_dlid (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_grh (struct rdma_ah_attr*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ah_set_path_bits (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (struct rdma_ah_attr*,scalar_t__) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_static_rate (struct rdma_ah_attr*,scalar_t__) ; 

__attribute__((used)) static void to_rdma_ah_attr(struct mlx4_ib_dev *ibdev,
			    struct rdma_ah_attr *ah_attr,
			    struct mlx4_qp_path *path)
{
	struct mlx4_dev *dev = ibdev->dev;
	u8 port_num = path->sched_queue & 0x40 ? 2 : 1;

	memset(ah_attr, 0, sizeof(*ah_attr));
	if (port_num == 0 || port_num > dev->caps.num_ports)
		return;
	ah_attr->type = rdma_ah_find_type(&ibdev->ib_dev, port_num);

	if (ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE)
		rdma_ah_set_sl(ah_attr, ((path->sched_queue >> 3) & 0x7) |
			       ((path->sched_queue & 4) << 1));
	else
		rdma_ah_set_sl(ah_attr, (path->sched_queue >> 2) & 0xf);
	rdma_ah_set_port_num(ah_attr, port_num);

	rdma_ah_set_dlid(ah_attr, be16_to_cpu(path->rlid));
	rdma_ah_set_path_bits(ah_attr, path->grh_mylmc & 0x7f);
	rdma_ah_set_static_rate(ah_attr,
				path->static_rate ? path->static_rate - 5 : 0);
	if (path->grh_mylmc & (1 << 7)) {
		rdma_ah_set_grh(ah_attr, NULL,
				be32_to_cpu(path->tclass_flowlabel) & 0xfffff,
				path->mgid_index,
				path->hop_limit,
				(be32_to_cpu(path->tclass_flowlabel)
				 >> 20) & 0xff);
		rdma_ah_set_dgid_raw(ah_attr, path->rgid);
	}
}