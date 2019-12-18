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
struct net_device {int dummy; } ;
struct in6_addr {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct dst_entry *rxe_find_route6(struct net_device *ndev,
					 struct in6_addr *saddr,
					 struct in6_addr *daddr)
{
	return NULL;
}