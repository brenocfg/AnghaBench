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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  dst_mac_msk; int /*<<< orphan*/  dst_mac; } ;
struct TYPE_3__ {int /*<<< orphan*/ * member_0; } ;
struct mlx4_spec_list {int /*<<< orphan*/  list; void* id; TYPE_2__ eth; TYPE_1__ member_0; } ;
struct mlx4_net_trans_rule {int allow_loopback; int port; int qpn; int /*<<< orphan*/  list; int /*<<< orphan*/  priority; int /*<<< orphan*/  promisc_mode; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  queue_mode; } ;
struct mlx4_dev {int dummy; } ;
typedef  unsigned char __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX4_FS_REGULAR ; 
 int MLX4_MAC_MASK ; 
 int /*<<< orphan*/  MLX4_NET_TRANS_Q_FIFO ; 
 void* MLX4_NET_TRANS_RULE_ID_ETH ; 
 void* MLX4_NET_TRANS_RULE_ID_VXLAN ; 
 unsigned char cpu_to_be64 (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int mlx4_flow_attach (struct mlx4_dev*,struct mlx4_net_trans_rule*,int /*<<< orphan*/ *) ; 

int mlx4_tunnel_steer_add(struct mlx4_dev *dev, unsigned char *addr,
			  int port, int qpn, u16 prio, u64 *reg_id)
{
	int err;
	struct mlx4_spec_list spec_eth_outer = { {NULL} };
	struct mlx4_spec_list spec_vxlan     = { {NULL} };
	struct mlx4_spec_list spec_eth_inner = { {NULL} };

	struct mlx4_net_trans_rule rule = {
		.queue_mode = MLX4_NET_TRANS_Q_FIFO,
		.exclusive = 0,
		.allow_loopback = 1,
		.promisc_mode = MLX4_FS_REGULAR,
	};

	__be64 mac_mask = cpu_to_be64(MLX4_MAC_MASK << 16);

	rule.port = port;
	rule.qpn = qpn;
	rule.priority = prio;
	INIT_LIST_HEAD(&rule.list);

	spec_eth_outer.id = MLX4_NET_TRANS_RULE_ID_ETH;
	memcpy(spec_eth_outer.eth.dst_mac, addr, ETH_ALEN);
	memcpy(spec_eth_outer.eth.dst_mac_msk, &mac_mask, ETH_ALEN);

	spec_vxlan.id = MLX4_NET_TRANS_RULE_ID_VXLAN;    /* any vxlan header */
	spec_eth_inner.id = MLX4_NET_TRANS_RULE_ID_ETH;	 /* any inner eth header */

	list_add_tail(&spec_eth_outer.list, &rule.list);
	list_add_tail(&spec_vxlan.list,     &rule.list);
	list_add_tail(&spec_eth_inner.list, &rule.list);

	err = mlx4_flow_attach(dev, &rule, reg_id);
	return err;
}