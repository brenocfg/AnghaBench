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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int /*<<< orphan*/  eeprom; } ;
struct eeprom_93cx6 {scalar_t__ reg_chip_select; scalar_t__ reg_data_clock; scalar_t__ reg_data_out; scalar_t__ reg_data_in; int /*<<< orphan*/  width; int /*<<< orphan*/  register_write; int /*<<< orphan*/  register_read; struct rt2x00_dev* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2PROM_CSR ; 
 int /*<<< orphan*/  E2PROM_CSR_TYPE ; 
 int /*<<< orphan*/  EEPROM_BASE ; 
 int EEPROM_SIZE ; 
 int /*<<< orphan*/  PCI_EEPROM_WIDTH_93C46 ; 
 int /*<<< orphan*/  PCI_EEPROM_WIDTH_93C66 ; 
 int /*<<< orphan*/  PCI_EEPROM_WIDTH_93C86 ; 
 int /*<<< orphan*/  eeprom_93cx6_multiread (struct eeprom_93cx6*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2800pci_eepromregister_read ; 
 int /*<<< orphan*/  rt2800pci_eepromregister_write ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2800pci_read_eeprom_pci(struct rt2x00_dev *rt2x00dev)
{
	struct eeprom_93cx6 eeprom;
	u32 reg;

	reg = rt2x00mmio_register_read(rt2x00dev, E2PROM_CSR);

	eeprom.data = rt2x00dev;
	eeprom.register_read = rt2800pci_eepromregister_read;
	eeprom.register_write = rt2800pci_eepromregister_write;
	switch (rt2x00_get_field32(reg, E2PROM_CSR_TYPE))
	{
	case 0:
		eeprom.width = PCI_EEPROM_WIDTH_93C46;
		break;
	case 1:
		eeprom.width = PCI_EEPROM_WIDTH_93C66;
		break;
	default:
		eeprom.width = PCI_EEPROM_WIDTH_93C86;
		break;
	}
	eeprom.reg_data_in = 0;
	eeprom.reg_data_out = 0;
	eeprom.reg_data_clock = 0;
	eeprom.reg_chip_select = 0;

	eeprom_93cx6_multiread(&eeprom, EEPROM_BASE, rt2x00dev->eeprom,
			       EEPROM_SIZE / sizeof(u16));

	return 0;
}