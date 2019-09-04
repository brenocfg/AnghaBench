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
typedef  int u16 ;
struct mlxsw_sp {TYPE_1__* router; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rifs; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  MAX_RIFS ; 
 int MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_rif_index_alloc(struct mlxsw_sp *mlxsw_sp, u16 *p_rif_index)
{
	int i;

	for (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS); i++) {
		if (!mlxsw_sp->router->rifs[i]) {
			*p_rif_index = i;
			return 0;
		}
	}

	return -ENOBUFS;
}