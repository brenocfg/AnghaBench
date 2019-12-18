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
struct mlx5e_ttc_table {int /*<<< orphan*/ ** tunnel_rules; int /*<<< orphan*/ ** rules; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int MLX5E_NUM_TT ; 
 int MLX5E_NUM_TUNNEL_TT ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_cleanup_ttc_rules(struct mlx5e_ttc_table *ttc)
{
	int i;

	for (i = 0; i < MLX5E_NUM_TT; i++) {
		if (!IS_ERR_OR_NULL(ttc->rules[i])) {
			mlx5_del_flow_rules(ttc->rules[i]);
			ttc->rules[i] = NULL;
		}
	}

	for (i = 0; i < MLX5E_NUM_TUNNEL_TT; i++) {
		if (!IS_ERR_OR_NULL(ttc->tunnel_rules[i])) {
			mlx5_del_flow_rules(ttc->tunnel_rules[i]);
			ttc->tunnel_rules[i] = NULL;
		}
	}
}