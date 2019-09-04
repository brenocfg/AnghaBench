#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union ib_gid {int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_gid_attr {int gid_type; TYPE_1__* ndev; } ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
#define  IB_GID_TYPE_IB 129 
#define  IB_GID_TYPE_ROCE_UDP_ENCAP 128 
 int /*<<< orphan*/  MLX5_ROCE_L3_TYPE_IPV4 ; 
 int /*<<< orphan*/  MLX5_ROCE_L3_TYPE_IPV6 ; 
 int /*<<< orphan*/  MLX5_ROCE_VERSION_1 ; 
 int /*<<< orphan*/  MLX5_ROCE_VERSION_2 ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_addr_v4mapped (void*) ; 
 scalar_t__ is_vlan_dev (TYPE_1__*) ; 
 int mlx5_core_roce_gid_set (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 int /*<<< orphan*/  vlan_dev_vlan_id (TYPE_1__*) ; 

__attribute__((used)) static int set_roce_addr(struct mlx5_ib_dev *dev, u8 port_num,
			 unsigned int index, const union ib_gid *gid,
			 const struct ib_gid_attr *attr)
{
	enum ib_gid_type gid_type = IB_GID_TYPE_IB;
	u8 roce_version = 0;
	u8 roce_l3_type = 0;
	bool vlan = false;
	u8 mac[ETH_ALEN];
	u16 vlan_id = 0;

	if (gid) {
		gid_type = attr->gid_type;
		ether_addr_copy(mac, attr->ndev->dev_addr);

		if (is_vlan_dev(attr->ndev)) {
			vlan = true;
			vlan_id = vlan_dev_vlan_id(attr->ndev);
		}
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
				      roce_l3_type, gid->raw, mac, vlan,
				      vlan_id, port_num);
}