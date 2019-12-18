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
 int /*<<< orphan*/  esw_destroy_offloads_acl_tables (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_offloads_fdb_tables (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_offloads_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_vport_rx_group (struct mlx5_eswitch*) ; 

__attribute__((used)) static void esw_offloads_steering_cleanup(struct mlx5_eswitch *esw)
{
	esw_destroy_vport_rx_group(esw);
	esw_destroy_offloads_table(esw);
	esw_destroy_offloads_fdb_tables(esw);
	esw_destroy_offloads_acl_tables(esw);
}