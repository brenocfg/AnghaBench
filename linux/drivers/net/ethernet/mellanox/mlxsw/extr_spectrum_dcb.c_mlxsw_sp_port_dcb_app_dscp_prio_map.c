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
struct mlxsw_sp_port {int /*<<< orphan*/  dev; } ;
struct dcb_ieee_app_dscp_map {scalar_t__* map; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  dcb_ieee_getapp_dscp_prio_mask_map (int /*<<< orphan*/ ,struct dcb_ieee_app_dscp_map*) ; 
 scalar_t__ fls (scalar_t__) ; 

__attribute__((used)) static void
mlxsw_sp_port_dcb_app_dscp_prio_map(struct mlxsw_sp_port *mlxsw_sp_port,
				    u8 default_prio,
				    struct dcb_ieee_app_dscp_map *map)
{
	int i;

	dcb_ieee_getapp_dscp_prio_mask_map(mlxsw_sp_port->dev, map);
	for (i = 0; i < ARRAY_SIZE(map->map); ++i) {
		if (map->map[i])
			map->map[i] = fls(map->map[i]) - 1;
		else
			map->map[i] = default_prio;
	}
}