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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {int mask; int /*<<< orphan*/  mask_ethtool; } ;

/* Variables and functions */
 int MLXSW_SP1_PORT_LINK_MODE_LEN ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 TYPE_1__* mlxsw_sp1_port_link_mode ; 

__attribute__((used)) static void
mlxsw_sp1_from_ptys_link(struct mlxsw_sp *mlxsw_sp, u32 ptys_eth_proto,
			 u8 width, unsigned long *mode)
{
	int i;

	for (i = 0; i < MLXSW_SP1_PORT_LINK_MODE_LEN; i++) {
		if (ptys_eth_proto & mlxsw_sp1_port_link_mode[i].mask)
			__set_bit(mlxsw_sp1_port_link_mode[i].mask_ethtool,
				  mode);
	}
}