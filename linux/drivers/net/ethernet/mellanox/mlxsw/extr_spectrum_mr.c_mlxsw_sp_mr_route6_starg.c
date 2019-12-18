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
struct mlxsw_sp_mr_table {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr6; } ;
struct TYPE_4__ {TYPE_1__ source_mask; } ;
struct mlxsw_sp_mr_route {TYPE_2__ key; } ;

/* Variables and functions */
 int ipv6_addr_any (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mlxsw_sp_mr_route6_starg(const struct mlxsw_sp_mr_table *mr_table,
				     const struct mlxsw_sp_mr_route *mr_route)
{
	return ipv6_addr_any(&mr_route->key.source_mask.addr6);
}