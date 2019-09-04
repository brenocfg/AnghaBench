#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  destructor; } ;
struct mlxsw_afa_mirror {int ingress; TYPE_3__ resource; int /*<<< orphan*/  local_in_port; int /*<<< orphan*/  span_id; } ;
struct mlxsw_afa_block {TYPE_1__* afa; } ;
struct TYPE_5__ {int (* mirror_add ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device const*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  ops_priv; TYPE_2__* ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_afa_mirror* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlxsw_afa_mirror*) ; 
 struct mlxsw_afa_mirror* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_mirror_destructor ; 
 int /*<<< orphan*/  mlxsw_afa_resource_add (struct mlxsw_afa_block*,TYPE_3__*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlxsw_afa_mirror *
mlxsw_afa_mirror_create(struct mlxsw_afa_block *block, u8 local_in_port,
			const struct net_device *out_dev, bool ingress)
{
	struct mlxsw_afa_mirror *mirror;
	int err;

	mirror = kzalloc(sizeof(*mirror), GFP_KERNEL);
	if (!mirror)
		return ERR_PTR(-ENOMEM);

	err = block->afa->ops->mirror_add(block->afa->ops_priv,
					  local_in_port, out_dev,
					  ingress, &mirror->span_id);
	if (err)
		goto err_mirror_add;

	mirror->ingress = ingress;
	mirror->local_in_port = local_in_port;
	mirror->resource.destructor = mlxsw_afa_mirror_destructor;
	mlxsw_afa_resource_add(block, &mirror->resource);
	return mirror;

err_mirror_add:
	kfree(mirror);
	return ERR_PTR(err);
}