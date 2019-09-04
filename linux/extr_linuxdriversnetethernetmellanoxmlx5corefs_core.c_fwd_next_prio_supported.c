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
struct mlx5_flow_table {scalar_t__ type; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 scalar_t__ FS_FT_NIC_RX ; 
 scalar_t__ MLX5_CAP_FLOWTABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nic_rx_multi_path_tirs ; 

__attribute__((used)) static bool fwd_next_prio_supported(struct mlx5_flow_table *ft)
{
	return ((ft->type == FS_FT_NIC_RX) &&
		(MLX5_CAP_FLOWTABLE(get_dev(&ft->node), nic_rx_multi_path_tirs)));
}