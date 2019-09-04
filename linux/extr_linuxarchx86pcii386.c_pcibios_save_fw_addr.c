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
struct pcibios_fwaddrmap {void** fw_addr; int /*<<< orphan*/  list; int /*<<< orphan*/  dev; } ;
struct pci_dev {int dummy; } ;
typedef  void* resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct pcibios_fwaddrmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 scalar_t__ pcibios_fw_addr_done ; 
 int /*<<< orphan*/  pcibios_fwaddrmap_lock ; 
 struct pcibios_fwaddrmap* pcibios_fwaddrmap_lookup (struct pci_dev*) ; 
 int /*<<< orphan*/  pcibios_fwaddrmappings ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
pcibios_save_fw_addr(struct pci_dev *dev, int idx, resource_size_t fw_addr)
{
	unsigned long flags;
	struct pcibios_fwaddrmap *map;

	if (pcibios_fw_addr_done)
		return;

	spin_lock_irqsave(&pcibios_fwaddrmap_lock, flags);
	map = pcibios_fwaddrmap_lookup(dev);
	if (!map) {
		spin_unlock_irqrestore(&pcibios_fwaddrmap_lock, flags);
		map = kzalloc(sizeof(*map), GFP_KERNEL);
		if (!map)
			return;

		map->dev = pci_dev_get(dev);
		map->fw_addr[idx] = fw_addr;
		INIT_LIST_HEAD(&map->list);

		spin_lock_irqsave(&pcibios_fwaddrmap_lock, flags);
		list_add_tail(&map->list, &pcibios_fwaddrmappings);
	} else
		map->fw_addr[idx] = fw_addr;
	spin_unlock_irqrestore(&pcibios_fwaddrmap_lock, flags);
}