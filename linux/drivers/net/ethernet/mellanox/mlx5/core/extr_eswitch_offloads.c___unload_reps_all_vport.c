#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  num_vfs; } ;
struct mlx5_eswitch {TYPE_1__ esw_funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unload_reps_special_vport (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __unload_reps_vf_vport (struct mlx5_eswitch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __unload_reps_all_vport(struct mlx5_eswitch *esw, u8 rep_type)
{
	__unload_reps_vf_vport(esw, esw->esw_funcs.num_vfs, rep_type);

	/* Special vports must be the last to unload. */
	__unload_reps_special_vport(esw, rep_type);
}