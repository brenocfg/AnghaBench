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
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_PORT_BASE_SPEED_25G ; 

__attribute__((used)) static int
mlxsw_sp1_port_speed_base(struct mlxsw_sp *mlxsw_sp, u8 local_port,
			  u32 *base_speed)
{
	*base_speed = MLXSW_SP_PORT_BASE_SPEED_25G;
	return 0;
}