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
 struct net_device* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct net_device* ipoib_alloc_netdev (struct ib_device*,int /*<<< orphan*/ ,char const*) ; 
 int ipoib_intf_init (struct ib_device*,int /*<<< orphan*/ ,char const*,struct net_device*) ; 

struct net_device *ipoib_intf_alloc(struct ib_device *hca, u8 port,
				    const char *name)
{
	struct net_device *dev;
	int rc;

	dev = ipoib_alloc_netdev(hca, port, name);
	if (IS_ERR(dev))
		return dev;

	rc = ipoib_intf_init(hca, port, name, dev);
	if (rc) {
		free_netdev(dev);
		return ERR_PTR(rc);
	}

	/*
	 * Upon success the caller must ensure ipoib_intf_free is called or
	 * register_netdevice succeed'd and priv_destructor is set to
	 * ipoib_intf_free.
	 */
	return dev;
}