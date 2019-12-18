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
struct mlxsw_sp {TYPE_1__* sb_vals; } ;
struct TYPE_2__ {int /*<<< orphan*/  cms_cpu_count; int /*<<< orphan*/  cms_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_SBXX_DIR_EGRESS ; 
 int __mlxsw_sp_sb_cms_init (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_cpu_port_sb_cms_init(struct mlxsw_sp *mlxsw_sp)
{
	return __mlxsw_sp_sb_cms_init(mlxsw_sp, 0, MLXSW_REG_SBXX_DIR_EGRESS,
				      mlxsw_sp->sb_vals->cms_cpu,
				      mlxsw_sp->sb_vals->cms_cpu_count);
}