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
struct mlxsw_sp {TYPE_1__* nve; } ;
struct TYPE_2__ {int /*<<< orphan*/  mc_list_ht; int /*<<< orphan*/  num_nve_tunnels; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

void mlxsw_sp_nve_fini(struct mlxsw_sp *mlxsw_sp)
{
	WARN_ON(mlxsw_sp->nve->num_nve_tunnels);
	rhashtable_destroy(&mlxsw_sp->nve->mc_list_ht);
	kfree(mlxsw_sp->nve);
	mlxsw_sp->nve = NULL;
}