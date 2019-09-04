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
struct fib6_info {int fib6_flags; } ;

/* Variables and functions */
 int RTF_ADDRCONF ; 
 int RTF_GATEWAY ; 

__attribute__((used)) static bool mlxsw_sp_fib6_rt_can_mp(const struct fib6_info *rt)
{
	/* RTF_CACHE routes are ignored */
	return (rt->fib6_flags & (RTF_GATEWAY | RTF_ADDRCONF)) == RTF_GATEWAY;
}