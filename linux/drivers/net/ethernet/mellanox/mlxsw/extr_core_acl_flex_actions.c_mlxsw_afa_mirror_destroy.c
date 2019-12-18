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
struct mlxsw_afa_mirror {int /*<<< orphan*/  ingress; int /*<<< orphan*/  span_id; int /*<<< orphan*/  local_in_port; int /*<<< orphan*/  resource; } ;
struct mlxsw_afa_block {TYPE_2__* afa; } ;
struct TYPE_4__ {int /*<<< orphan*/  ops_priv; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mirror_del ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_afa_mirror*) ; 
 int /*<<< orphan*/  mlxsw_afa_resource_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_afa_mirror_destroy(struct mlxsw_afa_block *block,
			 struct mlxsw_afa_mirror *mirror)
{
	mlxsw_afa_resource_del(&mirror->resource);
	block->afa->ops->mirror_del(block->afa->ops_priv,
				    mirror->local_in_port,
				    mirror->span_id,
				    mirror->ingress);
	kfree(mirror);
}