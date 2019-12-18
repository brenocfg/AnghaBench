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
#define  TC_SETUP_BLOCK 128 
 int flow_block_cb_setup_simple (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5e_priv*,struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  mlx5e_rep_block_cb_list ; 
 int /*<<< orphan*/  mlx5e_rep_setup_tc_cb ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_rep_setup_tc(struct net_device *dev, enum tc_setup_type type,
			      void *type_data)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct flow_block_offload *f = type_data;

	switch (type) {
	case TC_SETUP_BLOCK:
		f->unlocked_driver_cb = true;
		return flow_block_cb_setup_simple(type_data,
						  &mlx5e_rep_block_cb_list,
						  mlx5e_rep_setup_tc_cb,
						  priv, priv, true);
	default:
		return -EOPNOTSUPP;
	}
}