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
struct mlxsw_sp_port {int /*<<< orphan*/  dev; } ;
struct dcb_ieee_app_prio_map {scalar_t__* map; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  dcb_ieee_getapp_prio_dscp_mask_map (int /*<<< orphan*/ ,struct dcb_ieee_app_prio_map*) ; 
 scalar_t__ fls64 (scalar_t__) ; 

__attribute__((used)) static bool
mlxsw_sp_port_dcb_app_prio_dscp_map(struct mlxsw_sp_port *mlxsw_sp_port,
				    struct dcb_ieee_app_prio_map *map)
{
	bool have_dscp = false;
	int i;

	dcb_ieee_getapp_prio_dscp_mask_map(mlxsw_sp_port->dev, map);
	for (i = 0; i < ARRAY_SIZE(map->map); ++i) {
		if (map->map[i]) {
			map->map[i] = fls64(map->map[i]) - 1;
			have_dscp = true;
		}
	}

	return have_dscp;
}