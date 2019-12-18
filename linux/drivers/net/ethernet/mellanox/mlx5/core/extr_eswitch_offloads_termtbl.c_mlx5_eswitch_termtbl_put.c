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
struct mlx5_termtbl_handle {scalar_t__ ref_count; int /*<<< orphan*/  termtbl; int /*<<< orphan*/  rule; int /*<<< orphan*/  termtbl_hlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  termtbl_mutex; } ;
struct mlx5_eswitch {TYPE_1__ offloads; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5_termtbl_handle*) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void
mlx5_eswitch_termtbl_put(struct mlx5_eswitch *esw,
			 struct mlx5_termtbl_handle *tt)
{
	mutex_lock(&esw->offloads.termtbl_mutex);
	if (--tt->ref_count == 0)
		hash_del(&tt->termtbl_hlist);
	mutex_unlock(&esw->offloads.termtbl_mutex);

	if (!tt->ref_count) {
		mlx5_del_flow_rules(tt->rule);
		mlx5_destroy_flow_table(tt->termtbl);
		kfree(tt);
	}
}