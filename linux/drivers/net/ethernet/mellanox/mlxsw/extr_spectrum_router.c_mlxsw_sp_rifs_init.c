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
typedef  int /*<<< orphan*/  u64 ;
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp {TYPE_1__* router; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/  rifs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_RIFS ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_rifs_init(struct mlxsw_sp *mlxsw_sp)
{
	u64 max_rifs = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS);

	mlxsw_sp->router->rifs = kcalloc(max_rifs,
					 sizeof(struct mlxsw_sp_rif *),
					 GFP_KERNEL);
	if (!mlxsw_sp->router->rifs)
		return -ENOMEM;

	return 0;
}