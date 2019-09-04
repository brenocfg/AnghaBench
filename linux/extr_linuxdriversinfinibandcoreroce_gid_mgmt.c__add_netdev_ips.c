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
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IPV6 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_netdev_ipv4_ips (struct ib_device*,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  enum_netdev_ipv6_ips (struct ib_device*,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static void _add_netdev_ips(struct ib_device *ib_dev, u8 port,
			    struct net_device *ndev)
{
	enum_netdev_ipv4_ips(ib_dev, port, ndev);
	if (IS_ENABLED(CONFIG_IPV6))
		enum_netdev_ipv6_ips(ib_dev, port, ndev);
}