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
struct mlxsw_sib {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sib_port_remove (struct mlxsw_sib*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_port_fini (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sib_port_remove(struct mlxsw_sib *mlxsw_sib, u8 local_port)
{
	__mlxsw_sib_port_remove(mlxsw_sib, local_port);
	mlxsw_core_port_fini(mlxsw_sib->core, local_port);
}