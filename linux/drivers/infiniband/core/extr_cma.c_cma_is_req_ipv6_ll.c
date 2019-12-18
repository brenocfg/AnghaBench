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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct cma_req_info {int /*<<< orphan*/  listen_addr_storage; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cma_is_req_ipv6_ll(const struct cma_req_info *req)
{
	const struct sockaddr *daddr =
			(const struct sockaddr *)&req->listen_addr_storage;
	const struct sockaddr_in6 *daddr6 = (const struct sockaddr_in6 *)daddr;

	/* Returns true if the req is for IPv6 link local */
	return (daddr->sa_family == AF_INET6 &&
		(ipv6_addr_type(&daddr6->sin6_addr) & IPV6_ADDR_LINKLOCAL));
}