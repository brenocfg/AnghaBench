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
struct mlxsw_sp_nexthop {int should_offload; int update; } ;

/* Variables and functions */

__attribute__((used)) static void __mlxsw_sp_nexthop_neigh_update(struct mlxsw_sp_nexthop *nh,
					    bool removing)
{
	if (!removing)
		nh->should_offload = 1;
	else
		nh->should_offload = 0;
	nh->update = 1;
}