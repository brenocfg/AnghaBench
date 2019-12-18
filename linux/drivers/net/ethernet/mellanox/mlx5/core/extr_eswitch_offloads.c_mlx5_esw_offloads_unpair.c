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
struct mlx5_eswitch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  esw_del_fdb_peer_miss_rules (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5e_tc_clean_fdb_peer_flows (struct mlx5_eswitch*) ; 

__attribute__((used)) static void mlx5_esw_offloads_unpair(struct mlx5_eswitch *esw)
{
	mlx5e_tc_clean_fdb_peer_flows(esw);
	esw_del_fdb_peer_miss_rules(esw);
}