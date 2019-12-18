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
struct mlxsw_sp_fib_node {int /*<<< orphan*/  ht_node; } ;
struct mlxsw_sp_fib {int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_fib_ht_params ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_fib_node_remove(struct mlxsw_sp_fib *fib,
				     struct mlxsw_sp_fib_node *fib_node)
{
	rhashtable_remove_fast(&fib->ht, &fib_node->ht_node,
			       mlxsw_sp_fib_ht_params);
}