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
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct hp100_private {int mode; scalar_t__ mem_ptr_virt; int /*<<< orphan*/  page_vaddr_algn; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HP100_REGION_SIZE ; 
 scalar_t__ MAX_RINGSIZE ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  virt_to_whatever (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_dev(struct net_device *d)
{
	struct hp100_private *p = netdev_priv(d);

	unregister_netdev(d);
	release_region(d->base_addr, HP100_REGION_SIZE);

	if (p->mode == 1)	/* busmaster */
		pci_free_consistent(p->pci_dev, MAX_RINGSIZE + 0x0f,
				    p->page_vaddr_algn,
				    virt_to_whatever(d, p->page_vaddr_algn));
	if (p->mem_ptr_virt)
		iounmap(p->mem_ptr_virt);

	free_netdev(d);
}