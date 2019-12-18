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
struct net_device {int ifindex; } ;
struct ipoib_dev_priv {TYPE_1__* parent; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_FLAG_SUBINTERFACE ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device const*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_get_iflink(const struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	/* parent interface */
	if (!test_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags))
		return dev->ifindex;

	/* child/vlan interface */
	return priv->parent->ifindex;
}