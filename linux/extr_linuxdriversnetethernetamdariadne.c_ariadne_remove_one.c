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
struct zorro_dev {int dummy; } ;
struct net_device {int /*<<< orphan*/  mem_start; int /*<<< orphan*/  base_addr; } ;
struct Am79C960 {int dummy; } ;

/* Variables and functions */
 int ARIADNE_RAM_SIZE ; 
 int /*<<< orphan*/  ZTWO_PADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 struct net_device* zorro_get_drvdata (struct zorro_dev*) ; 

__attribute__((used)) static void ariadne_remove_one(struct zorro_dev *z)
{
	struct net_device *dev = zorro_get_drvdata(z);

	unregister_netdev(dev);
	release_mem_region(ZTWO_PADDR(dev->base_addr), sizeof(struct Am79C960));
	release_mem_region(ZTWO_PADDR(dev->mem_start), ARIADNE_RAM_SIZE);
	free_netdev(dev);
}