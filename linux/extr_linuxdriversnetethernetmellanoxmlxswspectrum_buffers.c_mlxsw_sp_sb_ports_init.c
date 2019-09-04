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
struct mlxsw_sp_sb_port {int dummy; } ;
struct mlxsw_sp {TYPE_1__* sb; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/  ports; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 unsigned int mlxsw_core_max_ports (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_sb_ports_init(struct mlxsw_sp *mlxsw_sp)
{
	unsigned int max_ports = mlxsw_core_max_ports(mlxsw_sp->core);

	mlxsw_sp->sb->ports = kcalloc(max_ports,
				      sizeof(struct mlxsw_sp_sb_port),
				      GFP_KERNEL);
	if (!mlxsw_sp->sb->ports)
		return -ENOMEM;
	return 0;
}