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
struct mlxsw_sp_mr_route_key {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
mlxsw_sp2_mr_tcam_route_destroy(struct mlxsw_sp *mlxsw_sp, void *priv,
				void *route_priv,
				struct mlxsw_sp_mr_route_key *key)
{
}