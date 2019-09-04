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
struct mlx5_esw_offload {int /*<<< orphan*/  ft_offloads; } ;
struct mlx5_eswitch {struct mlx5_esw_offload offloads; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_destroy_flow_table (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esw_destroy_offloads_table(struct mlx5_eswitch *esw)
{
	struct mlx5_esw_offload *offloads = &esw->offloads;

	mlx5_destroy_flow_table(offloads->ft_offloads);
}