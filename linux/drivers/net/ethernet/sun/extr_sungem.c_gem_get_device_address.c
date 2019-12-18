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
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; } ;
struct gem {struct net_device* dev; int /*<<< orphan*/  pdev; int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {unsigned char* id_ethaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  get_gem_mac_nonobp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* idprom ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 unsigned char* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int gem_get_device_address(struct gem *gp)
{
#if defined(CONFIG_SPARC) || defined(CONFIG_PPC_PMAC)
	struct net_device *dev = gp->dev;
	const unsigned char *addr;

	addr = of_get_property(gp->of_node, "local-mac-address", NULL);
	if (addr == NULL) {
#ifdef CONFIG_SPARC
		addr = idprom->id_ethaddr;
#else
		printk("\n");
		pr_err("%s: can't get mac-address\n", dev->name);
		return -1;
#endif
	}
	memcpy(dev->dev_addr, addr, ETH_ALEN);
#else
	get_gem_mac_nonobp(gp->pdev, gp->dev->dev_addr);
#endif
	return 0;
}