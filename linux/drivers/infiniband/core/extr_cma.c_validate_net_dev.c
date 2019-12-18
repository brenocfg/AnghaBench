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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int sa_family; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  validate_ipv4_net_dev (struct net_device*,struct sockaddr_in const*,struct sockaddr_in const*) ; 
 int /*<<< orphan*/  validate_ipv6_net_dev (struct net_device*,struct sockaddr_in6 const*,struct sockaddr_in6 const*) ; 

__attribute__((used)) static bool validate_net_dev(struct net_device *net_dev,
			     const struct sockaddr *daddr,
			     const struct sockaddr *saddr)
{
	const struct sockaddr_in *daddr4 = (const struct sockaddr_in *)daddr;
	const struct sockaddr_in *saddr4 = (const struct sockaddr_in *)saddr;
	const struct sockaddr_in6 *daddr6 = (const struct sockaddr_in6 *)daddr;
	const struct sockaddr_in6 *saddr6 = (const struct sockaddr_in6 *)saddr;

	switch (daddr->sa_family) {
	case AF_INET:
		return saddr->sa_family == AF_INET &&
		       validate_ipv4_net_dev(net_dev, daddr4, saddr4);

	case AF_INET6:
		return saddr->sa_family == AF_INET6 &&
		       validate_ipv6_net_dev(net_dev, daddr6, saddr6);

	default:
		return false;
	}
}