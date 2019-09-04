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
typedef  scalar_t__ u16 ;
struct mlxsw_res {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* mlxsw_res_ids ; 
 int /*<<< orphan*/  mlxsw_res_set (struct mlxsw_res*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_res_parse(struct mlxsw_res *res, u16 id, u64 value)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(mlxsw_res_ids); i++) {
		if (mlxsw_res_ids[i] == id) {
			mlxsw_res_set(res, i, value);
			return;
		}
	}
}