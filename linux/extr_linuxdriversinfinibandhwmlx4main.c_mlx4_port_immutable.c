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
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_ib_dev {TYPE_2__* dev; } ;
struct ib_port_immutable {int core_cap_flags; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; void* max_mad_size; } ;
struct ib_port_attr {int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int flags; int flags2; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 void* IB_MGMT_MAD_SIZE ; 
 int MLX4_DEV_CAP_FLAG2_ROCE_V1_V2 ; 
 int MLX4_DEV_CAP_FLAG_IBOE ; 
 int RDMA_CORE_PORT_IBA_IB ; 
 int RDMA_CORE_PORT_IBA_ROCE ; 
 int RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP ; 
 int RDMA_CORE_PORT_RAW_PACKET ; 
 int ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 scalar_t__ mlx4_ib_port_link_layer (struct ib_device*,int /*<<< orphan*/ ) ; 
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int mlx4_port_immutable(struct ib_device *ibdev, u8 port_num,
			       struct ib_port_immutable *immutable)
{
	struct ib_port_attr attr;
	struct mlx4_ib_dev *mdev = to_mdev(ibdev);
	int err;

	if (mlx4_ib_port_link_layer(ibdev, port_num) == IB_LINK_LAYER_INFINIBAND) {
		immutable->core_cap_flags = RDMA_CORE_PORT_IBA_IB;
		immutable->max_mad_size = IB_MGMT_MAD_SIZE;
	} else {
		if (mdev->dev->caps.flags & MLX4_DEV_CAP_FLAG_IBOE)
			immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE;
		if (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ROCE_V1_V2)
			immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE |
				RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP;
		immutable->core_cap_flags |= RDMA_CORE_PORT_RAW_PACKET;
		if (immutable->core_cap_flags & (RDMA_CORE_PORT_IBA_ROCE |
		    RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP))
			immutable->max_mad_size = IB_MGMT_MAD_SIZE;
	}

	err = ib_query_port(ibdev, port_num, &attr);
	if (err)
		return err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;

	return 0;
}