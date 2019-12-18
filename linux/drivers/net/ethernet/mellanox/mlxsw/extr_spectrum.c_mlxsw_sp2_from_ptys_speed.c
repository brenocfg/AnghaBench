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
typedef  int u32 ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {int mask; int speed; } ;

/* Variables and functions */
 int MLXSW_SP2_PORT_LINK_MODE_LEN ; 
 int SPEED_UNKNOWN ; 
 TYPE_1__* mlxsw_sp2_port_link_mode ; 

__attribute__((used)) static u32
mlxsw_sp2_from_ptys_speed(struct mlxsw_sp *mlxsw_sp, u32 ptys_eth_proto)
{
	int i;

	for (i = 0; i < MLXSW_SP2_PORT_LINK_MODE_LEN; i++) {
		if (ptys_eth_proto & mlxsw_sp2_port_link_mode[i].mask)
			return mlxsw_sp2_port_link_mode[i].speed;
	}

	return SPEED_UNKNOWN;
}