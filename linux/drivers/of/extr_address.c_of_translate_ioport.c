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
typedef  unsigned long u64 ;
struct device_node {int /*<<< orphan*/  fwnode; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned long OF_BAD_ADDR ; 
 unsigned long __of_translate_address (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,struct device_node**) ; 
 unsigned long logic_pio_trans_hwaddr (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  of_get_parent ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 unsigned long pci_address_to_pio (unsigned long) ; 

__attribute__((used)) static u64 of_translate_ioport(struct device_node *dev, const __be32 *in_addr,
			u64 size)
{
	u64 taddr;
	unsigned long port;
	struct device_node *host;

	taddr = __of_translate_address(dev, of_get_parent,
				       in_addr, "ranges", &host);
	if (host) {
		/* host-specific port access */
		port = logic_pio_trans_hwaddr(&host->fwnode, taddr, size);
		of_node_put(host);
	} else {
		/* memory-mapped I/O range */
		port = pci_address_to_pio(taddr);
	}

	if (port == (unsigned long)-1)
		return OF_BAD_ADDR;

	return port;
}