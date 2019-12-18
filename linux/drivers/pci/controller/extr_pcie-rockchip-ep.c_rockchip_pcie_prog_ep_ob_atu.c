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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct rockchip_pcie {TYPE_1__* mem_res; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int AXI_WRAPPER_NOR_MSG ; 
 int PCIE_CORE_OB_REGION_ADDR0_LO_ADDR ; 
 int PCIE_CORE_OB_REGION_ADDR0_NUM_BITS ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR0 (int) ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR1 (int) ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_DESC0 (int) ; 
 int ROCKCHIP_PCIE_AT_OB_REGION_DESC0_DEVFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_DESC1 (int) ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0 (int) ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR1 (int) ; 
 unsigned long long fls64 (size_t) ; 
 int ilog2 (unsigned long long) ; 
 int lower_32_bits (unsigned long long) ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int,int /*<<< orphan*/ ) ; 
 int upper_32_bits (unsigned long long) ; 

__attribute__((used)) static void rockchip_pcie_prog_ep_ob_atu(struct rockchip_pcie *rockchip, u8 fn,
					 u32 r, u32 type, u64 cpu_addr,
					 u64 pci_addr, size_t size)
{
	u64 sz = 1ULL << fls64(size - 1);
	int num_pass_bits = ilog2(sz);
	u32 addr0, addr1, desc0, desc1;
	bool is_nor_msg = (type == AXI_WRAPPER_NOR_MSG);

	/* The minimal region size is 1MB */
	if (num_pass_bits < 8)
		num_pass_bits = 8;

	cpu_addr -= rockchip->mem_res->start;
	addr0 = ((is_nor_msg ? 0x10 : (num_pass_bits - 1)) &
		PCIE_CORE_OB_REGION_ADDR0_NUM_BITS) |
		(lower_32_bits(cpu_addr) & PCIE_CORE_OB_REGION_ADDR0_LO_ADDR);
	addr1 = upper_32_bits(is_nor_msg ? cpu_addr : pci_addr);
	desc0 = ROCKCHIP_PCIE_AT_OB_REGION_DESC0_DEVFN(fn) | type;
	desc1 = 0;

	if (is_nor_msg) {
		rockchip_pcie_write(rockchip, 0,
				    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0(r));
		rockchip_pcie_write(rockchip, 0,
				    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR1(r));
		rockchip_pcie_write(rockchip, desc0,
				    ROCKCHIP_PCIE_AT_OB_REGION_DESC0(r));
		rockchip_pcie_write(rockchip, desc1,
				    ROCKCHIP_PCIE_AT_OB_REGION_DESC1(r));
	} else {
		/* PCI bus address region */
		rockchip_pcie_write(rockchip, addr0,
				    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0(r));
		rockchip_pcie_write(rockchip, addr1,
				    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR1(r));
		rockchip_pcie_write(rockchip, desc0,
				    ROCKCHIP_PCIE_AT_OB_REGION_DESC0(r));
		rockchip_pcie_write(rockchip, desc1,
				    ROCKCHIP_PCIE_AT_OB_REGION_DESC1(r));

		addr0 =
		    ((num_pass_bits - 1) & PCIE_CORE_OB_REGION_ADDR0_NUM_BITS) |
		    (lower_32_bits(cpu_addr) &
		     PCIE_CORE_OB_REGION_ADDR0_LO_ADDR);
		addr1 = upper_32_bits(cpu_addr);
	}

	/* CPU bus address region */
	rockchip_pcie_write(rockchip, addr0,
			    ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR0(r));
	rockchip_pcie_write(rockchip, addr1,
			    ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR1(r));
}