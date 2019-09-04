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
struct mlxsw_res {int* valid; } ;
typedef  enum mlxsw_res_id { ____Placeholder_mlxsw_res_id } mlxsw_res_id ;

/* Variables and functions */

__attribute__((used)) static inline bool mlxsw_res_valid(struct mlxsw_res *res,
				   enum mlxsw_res_id res_id)
{
	return res->valid[res_id];
}