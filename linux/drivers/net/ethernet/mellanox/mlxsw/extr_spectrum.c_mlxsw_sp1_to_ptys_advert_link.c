#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  mask_ethtool; } ;

/* Variables and functions */
 int MLXSW_SP1_PORT_LINK_MODE_LEN ; 
 TYPE_2__* mlxsw_sp1_port_link_mode ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
mlxsw_sp1_to_ptys_advert_link(struct mlxsw_sp *mlxsw_sp, u8 width,
			      const struct ethtool_link_ksettings *cmd)
{
	u32 ptys_proto = 0;
	int i;

	for (i = 0; i < MLXSW_SP1_PORT_LINK_MODE_LEN; i++) {
		if (test_bit(mlxsw_sp1_port_link_mode[i].mask_ethtool,
			     cmd->link_modes.advertising))
			ptys_proto |= mlxsw_sp1_port_link_mode[i].mask;
	}
	return ptys_proto;
}