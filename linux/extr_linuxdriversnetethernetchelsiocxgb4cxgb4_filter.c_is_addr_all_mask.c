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
struct in_addr {int s_addr; } ;
struct in6_addr {int* s6_addr32; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 

__attribute__((used)) static bool is_addr_all_mask(u8 *ipmask, int family)
{
	if (family == AF_INET) {
		struct in_addr *addr;

		addr = (struct in_addr *)ipmask;
		if (addr->s_addr == 0xffffffff)
			return true;
	} else if (family == AF_INET6) {
		struct in6_addr *addr6;

		addr6 = (struct in6_addr *)ipmask;
		if (addr6->s6_addr32[0] == 0xffffffff &&
		    addr6->s6_addr32[1] == 0xffffffff &&
		    addr6->s6_addr32[2] == 0xffffffff &&
		    addr6->s6_addr32[3] == 0xffffffff)
			return true;
	}
	return false;
}