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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 
 int MLXSW_SX_PORT_HW_STATS_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mlxsw_sx_port_hw_stats ; 

__attribute__((used)) static void mlxsw_sx_port_get_strings(struct net_device *dev,
				      u32 stringset, u8 *data)
{
	u8 *p = data;
	int i;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < MLXSW_SX_PORT_HW_STATS_LEN; i++) {
			memcpy(p, mlxsw_sx_port_hw_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		break;
	}
}