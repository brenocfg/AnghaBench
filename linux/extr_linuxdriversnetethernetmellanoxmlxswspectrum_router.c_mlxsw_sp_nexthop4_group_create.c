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
struct mlxsw_sp_nexthop_group {int count; struct mlxsw_sp_nexthop* nexthops; int /*<<< orphan*/  gateway; int /*<<< orphan*/ * neigh_tbl; int /*<<< orphan*/  fib_list; struct fib_info* priv; } ;
struct mlxsw_sp_nexthop {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct fib_nh {int dummy; } ;
struct fib_info {int fib_nhs; struct fib_nh* fib_nh; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_nexthop_group* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arp_tbl ; 
 int /*<<< orphan*/  fib_info_hold (struct fib_info*) ; 
 int /*<<< orphan*/  fib_info_put (struct fib_info*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_nexthop_group*) ; 
 struct mlxsw_sp_nexthop_group* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fi_is_gateway (struct mlxsw_sp*,struct fib_info*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop4_fini (struct mlxsw_sp*,struct mlxsw_sp_nexthop*) ; 
 int mlxsw_sp_nexthop4_init (struct mlxsw_sp*,struct mlxsw_sp_nexthop_group*,struct mlxsw_sp_nexthop*,struct fib_nh*) ; 
 int mlxsw_sp_nexthop_group_insert (struct mlxsw_sp*,struct mlxsw_sp_nexthop_group*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_group_refresh (struct mlxsw_sp*,struct mlxsw_sp_nexthop_group*) ; 

__attribute__((used)) static struct mlxsw_sp_nexthop_group *
mlxsw_sp_nexthop4_group_create(struct mlxsw_sp *mlxsw_sp, struct fib_info *fi)
{
	struct mlxsw_sp_nexthop_group *nh_grp;
	struct mlxsw_sp_nexthop *nh;
	struct fib_nh *fib_nh;
	size_t alloc_size;
	int i;
	int err;

	alloc_size = sizeof(*nh_grp) +
		     fi->fib_nhs * sizeof(struct mlxsw_sp_nexthop);
	nh_grp = kzalloc(alloc_size, GFP_KERNEL);
	if (!nh_grp)
		return ERR_PTR(-ENOMEM);
	nh_grp->priv = fi;
	INIT_LIST_HEAD(&nh_grp->fib_list);
	nh_grp->neigh_tbl = &arp_tbl;

	nh_grp->gateway = mlxsw_sp_fi_is_gateway(mlxsw_sp, fi);
	nh_grp->count = fi->fib_nhs;
	fib_info_hold(fi);
	for (i = 0; i < nh_grp->count; i++) {
		nh = &nh_grp->nexthops[i];
		fib_nh = &fi->fib_nh[i];
		err = mlxsw_sp_nexthop4_init(mlxsw_sp, nh_grp, nh, fib_nh);
		if (err)
			goto err_nexthop4_init;
	}
	err = mlxsw_sp_nexthop_group_insert(mlxsw_sp, nh_grp);
	if (err)
		goto err_nexthop_group_insert;
	mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh_grp);
	return nh_grp;

err_nexthop_group_insert:
err_nexthop4_init:
	for (i--; i >= 0; i--) {
		nh = &nh_grp->nexthops[i];
		mlxsw_sp_nexthop4_fini(mlxsw_sp, nh);
	}
	fib_info_put(fi);
	kfree(nh_grp);
	return ERR_PTR(err);
}