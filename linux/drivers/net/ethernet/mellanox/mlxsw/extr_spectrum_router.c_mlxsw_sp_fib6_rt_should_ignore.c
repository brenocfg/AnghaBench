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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct fib6_info {int fib6_flags; TYPE_1__ fib6_dst; } ;

/* Variables and functions */
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_MULTICAST ; 
 int RTF_CACHE ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mlxsw_sp_fib6_rt_should_ignore(const struct fib6_info *rt)
{
	/* Packets with link-local destination IP arriving to the router
	 * are trapped to the CPU, so no need to program specific routes
	 * for them.
	 */
	if (ipv6_addr_type(&rt->fib6_dst.addr) & IPV6_ADDR_LINKLOCAL)
		return true;

	/* Multicast routes aren't supported, so ignore them. Neighbour
	 * Discovery packets are specifically trapped.
	 */
	if (ipv6_addr_type(&rt->fib6_dst.addr) & IPV6_ADDR_MULTICAST)
		return true;

	/* Cloned routes are irrelevant in the forwarding path. */
	if (rt->fib6_flags & RTF_CACHE)
		return true;

	return false;
}