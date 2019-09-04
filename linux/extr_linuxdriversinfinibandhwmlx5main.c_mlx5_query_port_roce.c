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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct mlx5_ib_dev {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct ib_port_attr {int ip_gids; int max_msg_sz; int pkey_tbl_len; int phys_state; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  state; int /*<<< orphan*/  qkey_viol_cntr; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  active_width; int /*<<< orphan*/  active_speed; } ;
struct ib_device {int dummy; } ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MTU_4096 ; 
 int /*<<< orphan*/  IB_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_PORT_CM_SUP ; 
 int /*<<< orphan*/  IB_PORT_DOWN ; 
 int /*<<< orphan*/  IB_SPEED_QDR ; 
 int /*<<< orphan*/  IB_WIDTH_4X ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_ROCE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int iboe_get_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_max_msg ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 struct mlx5_core_dev* mlx5_ib_get_native_port_mdev (struct mlx5_ib_dev*,int,int*) ; 
 struct net_device* mlx5_ib_get_netdev (struct ib_device*,int) ; 
 int /*<<< orphan*/  mlx5_ib_put_native_port_mdev (struct mlx5_ib_dev*,int) ; 
 scalar_t__ mlx5_lag_is_active (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_query_nic_vport_qkey_viol_cntr (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int mlx5_query_port_eth_proto_oper (struct mlx5_core_dev*,int /*<<< orphan*/ *,int) ; 
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  roce_address_table_size ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 
 int /*<<< orphan*/  translate_eth_proto_oper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_query_port_roce(struct ib_device *device, u8 port_num,
				struct ib_port_attr *props)
{
	struct mlx5_ib_dev *dev = to_mdev(device);
	struct mlx5_core_dev *mdev;
	struct net_device *ndev, *upper;
	enum ib_mtu ndev_ib_mtu;
	bool put_mdev = true;
	u16 qkey_viol_cntr;
	u32 eth_prot_oper;
	u8 mdev_port_num;
	int err;

	mdev = mlx5_ib_get_native_port_mdev(dev, port_num, &mdev_port_num);
	if (!mdev) {
		/* This means the port isn't affiliated yet. Get the
		 * info for the master port instead.
		 */
		put_mdev = false;
		mdev = dev->mdev;
		mdev_port_num = 1;
		port_num = 1;
	}

	/* Possible bad flows are checked before filling out props so in case
	 * of an error it will still be zeroed out.
	 */
	err = mlx5_query_port_eth_proto_oper(mdev, &eth_prot_oper,
					     mdev_port_num);
	if (err)
		goto out;

	props->active_width     = IB_WIDTH_4X;
	props->active_speed     = IB_SPEED_QDR;

	translate_eth_proto_oper(eth_prot_oper, &props->active_speed,
				 &props->active_width);

	props->port_cap_flags |= IB_PORT_CM_SUP;
	props->ip_gids = true;

	props->gid_tbl_len      = MLX5_CAP_ROCE(dev->mdev,
						roce_address_table_size);
	props->max_mtu          = IB_MTU_4096;
	props->max_msg_sz       = 1 << MLX5_CAP_GEN(dev->mdev, log_max_msg);
	props->pkey_tbl_len     = 1;
	props->state            = IB_PORT_DOWN;
	props->phys_state       = 3;

	mlx5_query_nic_vport_qkey_viol_cntr(mdev, &qkey_viol_cntr);
	props->qkey_viol_cntr = qkey_viol_cntr;

	/* If this is a stub query for an unaffiliated port stop here */
	if (!put_mdev)
		goto out;

	ndev = mlx5_ib_get_netdev(device, port_num);
	if (!ndev)
		goto out;

	if (mlx5_lag_is_active(dev->mdev)) {
		rcu_read_lock();
		upper = netdev_master_upper_dev_get_rcu(ndev);
		if (upper) {
			dev_put(ndev);
			ndev = upper;
			dev_hold(ndev);
		}
		rcu_read_unlock();
	}

	if (netif_running(ndev) && netif_carrier_ok(ndev)) {
		props->state      = IB_PORT_ACTIVE;
		props->phys_state = 5;
	}

	ndev_ib_mtu = iboe_get_mtu(ndev->mtu);

	dev_put(ndev);

	props->active_mtu	= min(props->max_mtu, ndev_ib_mtu);
out:
	if (put_mdev)
		mlx5_ib_put_native_port_mdev(dev, port_num);
	return err;
}