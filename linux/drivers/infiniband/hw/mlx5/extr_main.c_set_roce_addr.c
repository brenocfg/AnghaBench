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
union ib_gid {int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_gid_attr {int gid_type; } ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;

/* Variables and functions */
 int ETH_ALEN ; 
#define  IB_GID_TYPE_IB 129 
#define  IB_GID_TYPE_ROCE_UDP_ENCAP 128 
 int /*<<< orphan*/  MLX5_ROCE_L3_TYPE_IPV4 ; 
 int /*<<< orphan*/  MLX5_ROCE_L3_TYPE_IPV6 ; 
 int /*<<< orphan*/  MLX5_ROCE_VERSION_1 ; 
 int /*<<< orphan*/  MLX5_ROCE_VERSION_2 ; 
 scalar_t__ VLAN_CFI_MASK ; 
 int /*<<< orphan*/  ipv6_addr_v4mapped (void*) ; 
 int mlx5_core_roce_gid_set (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 int rdma_read_gid_l2_fields (struct ib_gid_attr const*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_roce_addr(struct mlx5_ib_dev *dev, u8 port_num,
			 unsigned int index, const union ib_gid *gid,
			 const struct ib_gid_attr *attr)
{
	enum ib_gid_type gid_type = IB_GID_TYPE_IB;
	u16 vlan_id = 0xffff;
	u8 roce_version = 0;
	u8 roce_l3_type = 0;
	u8 mac[ETH_ALEN];
	int ret;

	if (gid) {
		gid_type = attr->gid_type;
		ret = rdma_read_gid_l2_fields(attr, &vlan_id, &mac[0]);
		if (ret)
			return ret;
	}

	switch (gid_type) {
	case IB_GID_TYPE_IB:
		roce_version = MLX5_ROCE_VERSION_1;
		break;
	case IB_GID_TYPE_ROCE_UDP_ENCAP:
		roce_version = MLX5_ROCE_VERSION_2;
		if (ipv6_addr_v4mapped((void *)gid))
			roce_l3_type = MLX5_ROCE_L3_TYPE_IPV4;
		else
			roce_l3_type = MLX5_ROCE_L3_TYPE_IPV6;
		break;

	default:
		mlx5_ib_warn(dev, "Unexpected GID type %u\n", gid_type);
	}

	return mlx5_core_roce_gid_set(dev->mdev, index, roce_version,
				      roce_l3_type, gid->raw, mac,
				      vlan_id < VLAN_CFI_MASK, vlan_id,
				      port_num);
}