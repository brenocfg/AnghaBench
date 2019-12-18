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
struct mlxsw_sp_sb_pr {int dummy; } ;
struct mlxsw_sp_sb_port {int dummy; } ;
struct mlxsw_sp {TYPE_2__* sb; TYPE_1__* sb_vals; int /*<<< orphan*/  core; } ;
struct TYPE_4__ {struct mlxsw_sp_sb_pr* ports; struct mlxsw_sp_sb_pr* prs; } ;
struct TYPE_3__ {unsigned int pool_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_sb_pr*) ; 
 unsigned int mlxsw_core_max_ports (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_sb_port_fini (struct mlxsw_sp_sb_pr*) ; 
 int mlxsw_sp_sb_port_init (struct mlxsw_sp*,struct mlxsw_sp_sb_pr*) ; 

__attribute__((used)) static int mlxsw_sp_sb_ports_init(struct mlxsw_sp *mlxsw_sp)
{
	unsigned int max_ports = mlxsw_core_max_ports(mlxsw_sp->core);
	struct mlxsw_sp_sb_pr *prs;
	int i;
	int err;

	mlxsw_sp->sb->ports = kcalloc(max_ports,
				      sizeof(struct mlxsw_sp_sb_port),
				      GFP_KERNEL);
	if (!mlxsw_sp->sb->ports)
		return -ENOMEM;

	prs = kcalloc(mlxsw_sp->sb_vals->pool_count, sizeof(*prs),
		      GFP_KERNEL);
	if (!prs) {
		err = -ENOMEM;
		goto err_alloc_prs;
	}
	mlxsw_sp->sb->prs = prs;

	for (i = 0; i < max_ports; i++) {
		err = mlxsw_sp_sb_port_init(mlxsw_sp, &mlxsw_sp->sb->ports[i]);
		if (err)
			goto err_sb_port_init;
	}

	return 0;

err_sb_port_init:
	for (i--; i >= 0; i--)
		mlxsw_sp_sb_port_fini(&mlxsw_sp->sb->ports[i]);
	kfree(mlxsw_sp->sb->prs);
err_alloc_prs:
	kfree(mlxsw_sp->sb->ports);
	return err;
}