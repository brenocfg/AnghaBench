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
typedef  int /*<<< orphan*/  u8 ;
struct in_addr {scalar_t__ s_addr; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int IPV6_ADDR_ANY ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int ipv6_addr_type (struct in6_addr const*) ; 

__attribute__((used)) static bool is_inaddr_any(u8 *ip, int family)
{
	int addr_type;

	if (family == AF_INET) {
		struct in_addr *addr;

		addr = (struct in_addr *)ip;
		if (addr->s_addr == htonl(INADDR_ANY))
			return true;
	} else if (family == AF_INET6) {
		struct in6_addr *addr6;

		addr6 = (struct in6_addr *)ip;
		addr_type = ipv6_addr_type((const struct in6_addr *)
					   &addr6);
		if (addr_type == IPV6_ADDR_ANY)
			return true;
	}
	return false;
}