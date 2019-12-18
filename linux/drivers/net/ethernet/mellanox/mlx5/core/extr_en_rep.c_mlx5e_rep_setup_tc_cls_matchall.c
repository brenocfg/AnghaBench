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
struct tc_cls_matchall_offload {int command; } ;
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSMATCHALL_DESTROY 130 
#define  TC_CLSMATCHALL_REPLACE 129 
#define  TC_CLSMATCHALL_STATS 128 
 int mlx5e_tc_configure_matchall (struct mlx5e_priv*,struct tc_cls_matchall_offload*) ; 
 int mlx5e_tc_delete_matchall (struct mlx5e_priv*,struct tc_cls_matchall_offload*) ; 
 int /*<<< orphan*/  mlx5e_tc_stats_matchall (struct mlx5e_priv*,struct tc_cls_matchall_offload*) ; 

__attribute__((used)) static
int mlx5e_rep_setup_tc_cls_matchall(struct mlx5e_priv *priv,
				    struct tc_cls_matchall_offload *ma)
{
	switch (ma->command) {
	case TC_CLSMATCHALL_REPLACE:
		return mlx5e_tc_configure_matchall(priv, ma);
	case TC_CLSMATCHALL_DESTROY:
		return mlx5e_tc_delete_matchall(priv, ma);
	case TC_CLSMATCHALL_STATS:
		mlx5e_tc_stats_matchall(priv, ma);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}