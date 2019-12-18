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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_PHYSICAL ; 
 int __mlxsw_core_port_init (struct mlxsw_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char const*,unsigned char) ; 

int mlxsw_core_port_init(struct mlxsw_core *mlxsw_core, u8 local_port,
			 u32 port_number, bool split,
			 u32 split_port_subnumber,
			 const unsigned char *switch_id,
			 unsigned char switch_id_len)
{
	return __mlxsw_core_port_init(mlxsw_core, local_port,
				      DEVLINK_PORT_FLAVOUR_PHYSICAL,
				      port_number, split, split_port_subnumber,
				      switch_id, switch_id_len);
}