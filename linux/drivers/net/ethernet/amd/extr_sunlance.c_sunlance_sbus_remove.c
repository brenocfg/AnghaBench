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
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;
struct lance_private {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  lance_free_hwresources (struct lance_private*) ; 
 struct lance_private* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int sunlance_sbus_remove(struct platform_device *op)
{
	struct lance_private *lp = platform_get_drvdata(op);
	struct net_device *net_dev = lp->dev;

	unregister_netdev(net_dev);

	lance_free_hwresources(lp);

	free_netdev(net_dev);

	return 0;
}