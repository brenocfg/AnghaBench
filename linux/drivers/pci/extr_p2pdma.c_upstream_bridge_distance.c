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
struct seq_buf {int dummy; } ;
struct pci_dev {TYPE_1__* p2pdma; } ;
typedef  enum pci_p2pdma_map_type { ____Placeholder_pci_p2pdma_map_type } pci_p2pdma_map_type ;
struct TYPE_2__ {int /*<<< orphan*/  map_types; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PCI_P2PDMA_MAP_NOT_SUPPORTED ; 
 int PCI_P2PDMA_MAP_THRU_HOST_BRIDGE ; 
 int __upstream_bridge_distance (struct pci_dev*,struct pci_dev*,int*,int*,struct seq_buf*) ; 
 int /*<<< orphan*/  host_bridge_whitelist (struct pci_dev*,struct pci_dev*) ; 
 int /*<<< orphan*/  map_types_idx (struct pci_dev*) ; 
 int /*<<< orphan*/  xa_mk_value (int) ; 
 int /*<<< orphan*/  xa_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum pci_p2pdma_map_type
upstream_bridge_distance(struct pci_dev *provider, struct pci_dev *client,
		int *dist, bool *acs_redirects, struct seq_buf *acs_list)
{
	enum pci_p2pdma_map_type map_type;

	map_type = __upstream_bridge_distance(provider, client, dist,
					      acs_redirects, acs_list);

	if (map_type == PCI_P2PDMA_MAP_THRU_HOST_BRIDGE) {
		if (!host_bridge_whitelist(provider, client))
			map_type = PCI_P2PDMA_MAP_NOT_SUPPORTED;
	}

	if (provider->p2pdma)
		xa_store(&provider->p2pdma->map_types, map_types_idx(client),
			 xa_mk_value(map_type), GFP_KERNEL);

	return map_type;
}