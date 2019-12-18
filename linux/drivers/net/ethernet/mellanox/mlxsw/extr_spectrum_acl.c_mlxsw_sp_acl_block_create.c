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
struct net {int dummy; } ;
struct mlxsw_sp_acl_block {struct net* net; struct mlxsw_sp* mlxsw_sp; int /*<<< orphan*/  binding_list; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_acl_block* kzalloc (int,int /*<<< orphan*/ ) ; 

struct mlxsw_sp_acl_block *mlxsw_sp_acl_block_create(struct mlxsw_sp *mlxsw_sp,
						     struct net *net)
{
	struct mlxsw_sp_acl_block *block;

	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (!block)
		return NULL;
	INIT_LIST_HEAD(&block->binding_list);
	block->mlxsw_sp = mlxsw_sp;
	block->net = net;
	return block;
}