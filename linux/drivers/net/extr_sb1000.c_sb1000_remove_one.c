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
struct pnp_dev {int dummy; } ;
struct net_device {int /*<<< orphan*/  mem_start; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct net_device* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void
sb1000_remove_one(struct pnp_dev *pdev)
{
	struct net_device *dev = pnp_get_drvdata(pdev);

	unregister_netdev(dev);
	release_region(dev->base_addr, 16);
	release_region(dev->mem_start, 16);
	free_netdev(dev);
}