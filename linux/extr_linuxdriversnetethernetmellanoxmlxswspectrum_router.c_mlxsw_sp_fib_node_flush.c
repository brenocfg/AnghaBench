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
struct mlxsw_sp_fib_node {TYPE_1__* fib; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {int proto; } ;

/* Variables and functions */
#define  MLXSW_SP_L3_PROTO_IPV4 129 
#define  MLXSW_SP_L3_PROTO_IPV6 128 
 int /*<<< orphan*/  mlxsw_sp_fib4_node_flush (struct mlxsw_sp*,struct mlxsw_sp_fib_node*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib6_node_flush (struct mlxsw_sp*,struct mlxsw_sp_fib_node*) ; 

__attribute__((used)) static void mlxsw_sp_fib_node_flush(struct mlxsw_sp *mlxsw_sp,
				    struct mlxsw_sp_fib_node *fib_node)
{
	switch (fib_node->fib->proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		mlxsw_sp_fib4_node_flush(mlxsw_sp, fib_node);
		break;
	case MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_sp_fib6_node_flush(mlxsw_sp, fib_node);
		break;
	}
}