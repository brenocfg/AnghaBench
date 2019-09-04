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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct flowi6 {int /*<<< orphan*/  flowi6_oif; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  fl6 ;

/* Variables and functions */
 int IPV6_ADDR_LINKLOCAL ; 
 int /*<<< orphan*/  init_net ; 
 struct dst_entry* ip6_route_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct flowi6*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dst_entry *i40iw_get_dst_ipv6(struct sockaddr_in6 *src_addr,
					    struct sockaddr_in6 *dst_addr)
{
	struct dst_entry *dst;
	struct flowi6 fl6;

	memset(&fl6, 0, sizeof(fl6));
	fl6.daddr = dst_addr->sin6_addr;
	fl6.saddr = src_addr->sin6_addr;
	if (ipv6_addr_type(&fl6.daddr) & IPV6_ADDR_LINKLOCAL)
		fl6.flowi6_oif = dst_addr->sin6_scope_id;

	dst = ip6_route_output(&init_net, NULL, &fl6);
	return dst;
}