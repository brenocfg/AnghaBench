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
struct net_device {int dummy; } ;
struct mlx5e_priv {int dummy; } ;
struct flow_block_offload {int unlocked_driver_cb; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_BLOCK 129 
#define  TC_SETUP_QDISC_MQPRIO 128 
 int flow_block_cb_setup_simple (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5e_priv*,struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  mlx5e_block_cb_list ; 
 int /*<<< orphan*/  mlx5e_setup_tc_block_cb ; 
 int mlx5e_setup_tc_mqprio (struct mlx5e_priv*,void*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_setup_tc(struct net_device *dev, enum tc_setup_type type,
			  void *type_data)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	switch (type) {
#ifdef CONFIG_MLX5_ESWITCH
	case TC_SETUP_BLOCK: {
		struct flow_block_offload *f = type_data;

		f->unlocked_driver_cb = true;
		return flow_block_cb_setup_simple(type_data,
						  &mlx5e_block_cb_list,
						  mlx5e_setup_tc_block_cb,
						  priv, priv, true);
	}
#endif
	case TC_SETUP_QDISC_MQPRIO:
		return mlx5e_setup_tc_mqprio(priv, type_data);
	default:
		return -EOPNOTSUPP;
	}
}