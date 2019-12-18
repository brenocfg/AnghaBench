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
struct mlxsw_sp_fib6_event_work {int nrt6; int /*<<< orphan*/ * rt_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_rt6_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_router_fib6_work_fini(struct mlxsw_sp_fib6_event_work *fib6_work)
{
	int i;

	for (i = 0; i < fib6_work->nrt6; i++)
		mlxsw_sp_rt6_release(fib6_work->rt_arr[i]);
	kfree(fib6_work->rt_arr);
}