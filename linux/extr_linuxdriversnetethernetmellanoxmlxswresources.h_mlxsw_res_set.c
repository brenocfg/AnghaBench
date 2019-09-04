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
typedef  int /*<<< orphan*/  u64 ;
struct mlxsw_res {int* valid; int /*<<< orphan*/ * values; } ;
typedef  enum mlxsw_res_id { ____Placeholder_mlxsw_res_id } mlxsw_res_id ;

/* Variables and functions */

__attribute__((used)) static inline void mlxsw_res_set(struct mlxsw_res *res,
				 enum mlxsw_res_id res_id, u64 value)
{
	res->valid[res_id] = true;
	res->values[res_id] = value;
}