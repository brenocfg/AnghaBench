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
 int esw_create_offloads_fdb_tables (struct mlx5_eswitch*,int) ; 
 int esw_create_offloads_table (struct mlx5_eswitch*) ; 
 int esw_create_vport_rx_group (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_offloads_fdb_tables (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_offloads_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_vport_rx_group (struct mlx5_eswitch*) ; 
 int esw_offloads_load_reps (struct mlx5_eswitch*,int) ; 

int esw_offloads_init(struct mlx5_eswitch *esw, int nvports)
{
	int err;

	err = esw_create_offloads_fdb_tables(esw, nvports);
	if (err)
		return err;

	err = esw_create_offloads_table(esw);
	if (err)
		goto create_ft_err;

	err = esw_create_vport_rx_group(esw);
	if (err)
		goto create_fg_err;

	err = esw_offloads_load_reps(esw, nvports);
	if (err)
		goto err_reps;

	return 0;

err_reps:
	esw_destroy_vport_rx_group(esw);

create_fg_err:
	esw_destroy_offloads_table(esw);

create_ft_err:
	esw_destroy_offloads_fdb_tables(esw);

	return err;
}