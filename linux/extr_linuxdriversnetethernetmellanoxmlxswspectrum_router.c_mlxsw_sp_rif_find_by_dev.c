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
struct net_device {int dummy; } ;
struct mlxsw_sp_rif {struct net_device const* dev; } ;
struct mlxsw_sp {TYPE_1__* router; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {struct mlxsw_sp_rif** rifs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RIFS ; 
 int MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct mlxsw_sp_rif *
mlxsw_sp_rif_find_by_dev(const struct mlxsw_sp *mlxsw_sp,
			 const struct net_device *dev)
{
	int i;

	for (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS); i++)
		if (mlxsw_sp->router->rifs[i] &&
		    mlxsw_sp->router->rifs[i]->dev == dev)
			return mlxsw_sp->router->rifs[i];

	return NULL;
}