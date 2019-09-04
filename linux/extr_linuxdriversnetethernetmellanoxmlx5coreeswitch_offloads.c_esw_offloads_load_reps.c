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
typedef  scalar_t__ u8 ;
struct mlx5_eswitch {int dummy; } ;

/* Variables and functions */
 scalar_t__ NUM_REP_TYPES ; 
 int esw_offloads_load_reps_type (struct mlx5_eswitch*,int,scalar_t__) ; 
 int /*<<< orphan*/  esw_offloads_unload_reps_type (struct mlx5_eswitch*,int,scalar_t__) ; 

__attribute__((used)) static int esw_offloads_load_reps(struct mlx5_eswitch *esw, int nvports)
{
	u8 rep_type = 0;
	int err;

	for (rep_type = 0; rep_type < NUM_REP_TYPES; rep_type++) {
		err = esw_offloads_load_reps_type(esw, nvports, rep_type);
		if (err)
			goto err_reps;
	}

	return err;

err_reps:
	while (rep_type-- > 0)
		esw_offloads_unload_reps_type(esw, nvports, rep_type);
	return err;
}