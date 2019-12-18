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
struct fib6_info {int fib6_flags; TYPE_1__* fib6_nh; } ;
struct TYPE_2__ {scalar_t__ fib_nh_gw_family; } ;

/* Variables and functions */
 int RTF_ADDRCONF ; 

__attribute__((used)) static bool mlxsw_sp_fib6_rt_can_mp(const struct fib6_info *rt)
{
	/* RTF_CACHE routes are ignored */
	return !(rt->fib6_flags & RTF_ADDRCONF) &&
		rt->fib6_nh->fib_nh_gw_family;
}