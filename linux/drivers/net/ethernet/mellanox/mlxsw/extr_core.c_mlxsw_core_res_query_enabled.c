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
struct mlxsw_core {TYPE_1__* driver; } ;
struct TYPE_2__ {int res_query_enabled; } ;

/* Variables and functions */

bool mlxsw_core_res_query_enabled(const struct mlxsw_core *mlxsw_core)
{
	return mlxsw_core->driver->res_query_enabled;
}