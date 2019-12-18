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

/* Variables and functions */
 scalar_t__ dcb_ieee_getapp_default_prio_mask (int /*<<< orphan*/ ) ; 
 scalar_t__ fls (scalar_t__) ; 

__attribute__((used)) static u8
mlxsw_sp_port_dcb_app_default_prio(struct mlxsw_sp_port *mlxsw_sp_port)
{
	u8 prio_mask;

	prio_mask = dcb_ieee_getapp_default_prio_mask(mlxsw_sp_port->dev);
	if (prio_mask)
		/* Take the highest configured priority. */
		return fls(prio_mask) - 1;

	return 0;
}