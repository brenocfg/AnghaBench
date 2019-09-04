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
typedef  int u8 ;
struct aper_size_info_8 {int size_value; } ;
struct TYPE_2__ {scalar_t__ apbase_config; int gart_bus_addr; int gatt_bus_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  current_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_APBASE ; 
 int /*<<< orphan*/  AGP_APERTURE_BAR ; 
 struct aper_size_info_8* A_SIZE_8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_AGPCTRL ; 
 int /*<<< orphan*/  INTEL_APSIZE ; 
 int /*<<< orphan*/  INTEL_ATTBASE ; 
 int /*<<< orphan*/  INTEL_I845_AGPM ; 
 int /*<<< orphan*/  INTEL_I845_ERRSTS ; 
 TYPE_1__* agp_bridge ; 
 int pci_bus_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int intel_845_configure(void)
{
	u8 temp2;
	struct aper_size_info_8 *current_size;

	current_size = A_SIZE_8(agp_bridge->current_size);

	/* aperture size */
	pci_write_config_byte(agp_bridge->dev, INTEL_APSIZE, current_size->size_value);

	if (agp_bridge->apbase_config != 0) {
		pci_write_config_dword(agp_bridge->dev, AGP_APBASE,
				       agp_bridge->apbase_config);
	} else {
		/* address to map to */
		agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
							    AGP_APERTURE_BAR);
		agp_bridge->apbase_config = agp_bridge->gart_bus_addr;
	}

	/* attbase - aperture base */
	pci_write_config_dword(agp_bridge->dev, INTEL_ATTBASE, agp_bridge->gatt_bus_addr);

	/* agpctrl */
	pci_write_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x0000);

	/* agpm */
	pci_read_config_byte(agp_bridge->dev, INTEL_I845_AGPM, &temp2);
	pci_write_config_byte(agp_bridge->dev, INTEL_I845_AGPM, temp2 | (1 << 1));
	/* clear any possible error conditions */
	pci_write_config_word(agp_bridge->dev, INTEL_I845_ERRSTS, 0x001c);
	return 0;
}