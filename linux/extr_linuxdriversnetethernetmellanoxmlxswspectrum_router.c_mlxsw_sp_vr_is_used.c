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
struct mlxsw_sp_vr {int /*<<< orphan*/ * mr_table; int /*<<< orphan*/  fib6; int /*<<< orphan*/  fib4; } ;

/* Variables and functions */
 size_t MLXSW_SP_L3_PROTO_IPV4 ; 
 size_t MLXSW_SP_L3_PROTO_IPV6 ; 

__attribute__((used)) static bool mlxsw_sp_vr_is_used(const struct mlxsw_sp_vr *vr)
{
	return !!vr->fib4 || !!vr->fib6 ||
	       !!vr->mr_table[MLXSW_SP_L3_PROTO_IPV4] ||
	       !!vr->mr_table[MLXSW_SP_L3_PROTO_IPV6];
}