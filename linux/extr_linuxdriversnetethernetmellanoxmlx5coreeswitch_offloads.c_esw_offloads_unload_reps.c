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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_eswitch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_REP_TYPES ; 
 int /*<<< orphan*/  esw_offloads_unload_reps_type (struct mlx5_eswitch*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esw_offloads_unload_reps(struct mlx5_eswitch *esw, int nvports)
{
	u8 rep_type = NUM_REP_TYPES;

	while (rep_type-- > 0)
		esw_offloads_unload_reps_type(esw, nvports, rep_type);
}