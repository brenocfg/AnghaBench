#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/ * dst_mac_msk; int /*<<< orphan*/ * dst_mac; } ;
struct TYPE_5__ {int /*<<< orphan*/ * member_0; } ;
struct mlx4_spec_list {int /*<<< orphan*/  list; TYPE_3__ eth; int /*<<< orphan*/  id; TYPE_2__ member_0; } ;
struct mlx4_qp {int qpn; } ;
struct mlx4_net_trans_rule {int allow_loopback; int qpn; int /*<<< orphan*/  list; int /*<<< orphan*/  port; int /*<<< orphan*/  priority; int /*<<< orphan*/  promisc_mode; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  queue_mode; } ;
struct mlx4_en_priv {int /*<<< orphan*/  port; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {struct mlx4_dev* dev; } ;
struct TYPE_4__ {int steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
typedef  unsigned char __be64 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX4_DOMAIN_NIC ; 
 int /*<<< orphan*/  MLX4_FS_REGULAR ; 
 int MLX4_MAC_MASK ; 
 int /*<<< orphan*/  MLX4_NET_TRANS_Q_FIFO ; 
 int /*<<< orphan*/  MLX4_NET_TRANS_RULE_ID_ETH ; 
 int /*<<< orphan*/  MLX4_PROT_ETH ; 
#define  MLX4_STEERING_MODE_B0 129 
#define  MLX4_STEERING_MODE_DEVICE_MANAGED 128 
 unsigned char cpu_to_be64 (int) ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int mlx4_flow_attach (struct mlx4_dev*,struct mlx4_net_trans_rule*,int /*<<< orphan*/ *) ; 
 int mlx4_unicast_attach (struct mlx4_dev*,struct mlx4_qp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_en_uc_steer_add(struct mlx4_en_priv *priv,
				unsigned char *mac, int *qpn, u64 *reg_id)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_dev *dev = mdev->dev;
	int err;

	switch (dev->caps.steering_mode) {
	case MLX4_STEERING_MODE_B0: {
		struct mlx4_qp qp;
		u8 gid[16] = {0};

		qp.qpn = *qpn;
		memcpy(&gid[10], mac, ETH_ALEN);
		gid[5] = priv->port;

		err = mlx4_unicast_attach(dev, &qp, gid, 0, MLX4_PROT_ETH);
		break;
	}
	case MLX4_STEERING_MODE_DEVICE_MANAGED: {
		struct mlx4_spec_list spec_eth = { {NULL} };
		__be64 mac_mask = cpu_to_be64(MLX4_MAC_MASK << 16);

		struct mlx4_net_trans_rule rule = {
			.queue_mode = MLX4_NET_TRANS_Q_FIFO,
			.exclusive = 0,
			.allow_loopback = 1,
			.promisc_mode = MLX4_FS_REGULAR,
			.priority = MLX4_DOMAIN_NIC,
		};

		rule.port = priv->port;
		rule.qpn = *qpn;
		INIT_LIST_HEAD(&rule.list);

		spec_eth.id = MLX4_NET_TRANS_RULE_ID_ETH;
		memcpy(spec_eth.eth.dst_mac, mac, ETH_ALEN);
		memcpy(spec_eth.eth.dst_mac_msk, &mac_mask, ETH_ALEN);
		list_add_tail(&spec_eth.list, &rule.list);

		err = mlx4_flow_attach(dev, &rule, reg_id);
		break;
	}
	default:
		return -EINVAL;
	}
	if (err)
		en_warn(priv, "Failed Attaching Unicast\n");

	return err;
}