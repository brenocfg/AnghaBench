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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct v3_pci {struct device* dev; } ;
struct of_pci_range {int cpu_addr; int size; int pci_addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SZ_128M 139 
#define  SZ_16M 138 
#define  SZ_1G 137 
#define  SZ_1M 136 
#define  SZ_256M 135 
#define  SZ_2G 134 
#define  SZ_2M 133 
#define  SZ_32M 132 
#define  SZ_4M 131 
#define  SZ_512M 130 
#define  SZ_64M 129 
#define  SZ_8M 128 
 int V3_LB_BASE_ADR_SIZE_128MB ; 
 int V3_LB_BASE_ADR_SIZE_16MB ; 
 int V3_LB_BASE_ADR_SIZE_1GB ; 
 int V3_LB_BASE_ADR_SIZE_1MB ; 
 int V3_LB_BASE_ADR_SIZE_256MB ; 
 int V3_LB_BASE_ADR_SIZE_2GB ; 
 int V3_LB_BASE_ADR_SIZE_2MB ; 
 int V3_LB_BASE_ADR_SIZE_32MB ; 
 int V3_LB_BASE_ADR_SIZE_4MB ; 
 int V3_LB_BASE_ADR_SIZE_512MB ; 
 int V3_LB_BASE_ADR_SIZE_64MB ; 
 int V3_LB_BASE_ADR_SIZE_8MB ; 
 int V3_PCI_BASE_M_ADR_BASE ; 
 int V3_PCI_MAP_M_ENABLE ; 
 int V3_PCI_MAP_M_MAP_ADR ; 
 int V3_PCI_MAP_M_REG_EN ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,scalar_t__,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int v3_get_dma_range_config(struct v3_pci *v3,
				   struct of_pci_range *range,
				   u32 *pci_base, u32 *pci_map)
{
	struct device *dev = v3->dev;
	u64 cpu_end = range->cpu_addr + range->size - 1;
	u64 pci_end = range->pci_addr + range->size - 1;
	u32 val;

	if (range->pci_addr & ~V3_PCI_BASE_M_ADR_BASE) {
		dev_err(dev, "illegal range, only PCI bits 31..20 allowed\n");
		return -EINVAL;
	}
	val = ((u32)range->pci_addr) & V3_PCI_BASE_M_ADR_BASE;
	*pci_base = val;

	if (range->cpu_addr & ~V3_PCI_MAP_M_MAP_ADR) {
		dev_err(dev, "illegal range, only CPU bits 31..20 allowed\n");
		return -EINVAL;
	}
	val = ((u32)range->cpu_addr) & V3_PCI_MAP_M_MAP_ADR;

	switch (range->size) {
	case SZ_1M:
		val |= V3_LB_BASE_ADR_SIZE_1MB;
		break;
	case SZ_2M:
		val |= V3_LB_BASE_ADR_SIZE_2MB;
		break;
	case SZ_4M:
		val |= V3_LB_BASE_ADR_SIZE_4MB;
		break;
	case SZ_8M:
		val |= V3_LB_BASE_ADR_SIZE_8MB;
		break;
	case SZ_16M:
		val |= V3_LB_BASE_ADR_SIZE_16MB;
		break;
	case SZ_32M:
		val |= V3_LB_BASE_ADR_SIZE_32MB;
		break;
	case SZ_64M:
		val |= V3_LB_BASE_ADR_SIZE_64MB;
		break;
	case SZ_128M:
		val |= V3_LB_BASE_ADR_SIZE_128MB;
		break;
	case SZ_256M:
		val |= V3_LB_BASE_ADR_SIZE_256MB;
		break;
	case SZ_512M:
		val |= V3_LB_BASE_ADR_SIZE_512MB;
		break;
	case SZ_1G:
		val |= V3_LB_BASE_ADR_SIZE_1GB;
		break;
	case SZ_2G:
		val |= V3_LB_BASE_ADR_SIZE_2GB;
		break;
	default:
		dev_err(v3->dev, "illegal dma memory chunk size\n");
		return -EINVAL;
		break;
	}
	val |= V3_PCI_MAP_M_REG_EN | V3_PCI_MAP_M_ENABLE;
	*pci_map = val;

	dev_dbg(dev,
		"DMA MEM CPU: 0x%016llx -> 0x%016llx => "
		"PCI: 0x%016llx -> 0x%016llx base %08x map %08x\n",
		range->cpu_addr, cpu_end,
		range->pci_addr, pci_end,
		*pci_base, *pci_map);

	return 0;
}