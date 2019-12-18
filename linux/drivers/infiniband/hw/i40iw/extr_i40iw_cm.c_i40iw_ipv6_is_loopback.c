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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  u6_addr32; } ;
struct in6_addr {TYPE_1__ in6_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_copy_ip_htonl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ipv6_addr_loopback (struct in6_addr*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool i40iw_ipv6_is_loopback(u32 *loc_addr, u32 *rem_addr)
{
	struct in6_addr raddr6;

	i40iw_copy_ip_htonl(raddr6.in6_u.u6_addr32, rem_addr);
	return !memcmp(loc_addr, rem_addr, 16) || ipv6_addr_loopback(&raddr6);
}