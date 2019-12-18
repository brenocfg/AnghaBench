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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct rockchip_pcie {int dummy; } ;
struct rockchip_pcie_ep {int max_regions; int /*<<< orphan*/ * ob_addr; int /*<<< orphan*/  ob_region_map; struct rockchip_pcie rockchip; } ;
struct pci_epc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_WRAPPER_MEM_WRITE ; 
 int BITS_PER_LONG ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct rockchip_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 int find_first_zero_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rockchip_pcie_prog_ep_ob_atu (struct rockchip_pcie*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rockchip_pcie_ep_map_addr(struct pci_epc *epc, u8 fn,
				     phys_addr_t addr, u64 pci_addr,
				     size_t size)
{
	struct rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	struct rockchip_pcie *pcie = &ep->rockchip;
	u32 r;

	r = find_first_zero_bit(&ep->ob_region_map,
				sizeof(ep->ob_region_map) * BITS_PER_LONG);
	/*
	 * Region 0 is reserved for configuration space and shouldn't
	 * be used elsewhere per TRM, so leave it out.
	 */
	if (r >= ep->max_regions - 1) {
		dev_err(&epc->dev, "no free outbound region\n");
		return -EINVAL;
	}

	rockchip_pcie_prog_ep_ob_atu(pcie, fn, r, AXI_WRAPPER_MEM_WRITE, addr,
				     pci_addr, size);

	set_bit(r, &ep->ob_region_map);
	ep->ob_addr[r] = addr;

	return 0;
}