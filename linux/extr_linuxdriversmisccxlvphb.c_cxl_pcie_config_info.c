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
struct pci_bus {int /*<<< orphan*/  number; } ;
struct cxl_afu {int crs_num; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int cxl_pcie_cfg_record (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int cxl_pcie_config_info(struct pci_bus *bus, unsigned int devfn,
				       struct cxl_afu *afu, int *_record)
{
	int record;

	record = cxl_pcie_cfg_record(bus->number, devfn);
	if (record > afu->crs_num)
		return PCIBIOS_DEVICE_NOT_FOUND;

	*_record = record;
	return 0;
}