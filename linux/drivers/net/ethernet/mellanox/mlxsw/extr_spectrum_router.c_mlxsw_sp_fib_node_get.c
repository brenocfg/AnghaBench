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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_vr {int dummy; } ;
struct mlxsw_sp_fib_node {int dummy; } ;
struct mlxsw_sp_fib {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_fib_node* ERR_CAST (struct mlxsw_sp_vr*) ; 
 struct mlxsw_sp_fib_node* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_vr*) ; 
 struct mlxsw_sp_fib_node* mlxsw_sp_fib_node_create (struct mlxsw_sp_fib*,void const*,size_t,unsigned char) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_node_destroy (struct mlxsw_sp_fib_node*) ; 
 int mlxsw_sp_fib_node_init (struct mlxsw_sp*,struct mlxsw_sp_fib_node*,struct mlxsw_sp_fib*) ; 
 struct mlxsw_sp_fib_node* mlxsw_sp_fib_node_lookup (struct mlxsw_sp_fib*,void const*,size_t,unsigned char) ; 
 struct mlxsw_sp_fib* mlxsw_sp_vr_fib (struct mlxsw_sp_vr*,int) ; 
 struct mlxsw_sp_vr* mlxsw_sp_vr_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_vr_put (struct mlxsw_sp*,struct mlxsw_sp_vr*) ; 

__attribute__((used)) static struct mlxsw_sp_fib_node *
mlxsw_sp_fib_node_get(struct mlxsw_sp *mlxsw_sp, u32 tb_id, const void *addr,
		      size_t addr_len, unsigned char prefix_len,
		      enum mlxsw_sp_l3proto proto)
{
	struct mlxsw_sp_fib_node *fib_node;
	struct mlxsw_sp_fib *fib;
	struct mlxsw_sp_vr *vr;
	int err;

	vr = mlxsw_sp_vr_get(mlxsw_sp, tb_id, NULL);
	if (IS_ERR(vr))
		return ERR_CAST(vr);
	fib = mlxsw_sp_vr_fib(vr, proto);

	fib_node = mlxsw_sp_fib_node_lookup(fib, addr, addr_len, prefix_len);
	if (fib_node)
		return fib_node;

	fib_node = mlxsw_sp_fib_node_create(fib, addr, addr_len, prefix_len);
	if (!fib_node) {
		err = -ENOMEM;
		goto err_fib_node_create;
	}

	err = mlxsw_sp_fib_node_init(mlxsw_sp, fib_node, fib);
	if (err)
		goto err_fib_node_init;

	return fib_node;

err_fib_node_init:
	mlxsw_sp_fib_node_destroy(fib_node);
err_fib_node_create:
	mlxsw_sp_vr_put(mlxsw_sp, vr);
	return ERR_PTR(err);
}