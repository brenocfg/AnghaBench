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
struct mlx5e_rep_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flow_indr_block_cb_unregister (struct net_device*,int /*<<< orphan*/ ,struct mlx5e_rep_priv*) ; 
 int /*<<< orphan*/  mlx5e_rep_indr_setup_tc_cb ; 

__attribute__((used)) static void mlx5e_rep_indr_unregister_block(struct mlx5e_rep_priv *rpriv,
					    struct net_device *netdev)
{
	__flow_indr_block_cb_unregister(netdev, mlx5e_rep_indr_setup_tc_cb,
					rpriv);
}