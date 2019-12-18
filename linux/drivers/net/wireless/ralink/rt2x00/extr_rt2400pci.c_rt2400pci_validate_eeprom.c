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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rt2x00_dev {int /*<<< orphan*/  eeprom; } ;
struct eeprom_93cx6 {scalar_t__ reg_chip_select; scalar_t__ reg_data_clock; scalar_t__ reg_data_out; scalar_t__ reg_data_in; int /*<<< orphan*/  width; int /*<<< orphan*/  register_write; int /*<<< orphan*/  register_read; struct rt2x00_dev* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR21 ; 
 int /*<<< orphan*/  CSR21_TYPE_93C46 ; 
 int /*<<< orphan*/  EEPROM_ANTENNA ; 
 int /*<<< orphan*/  EEPROM_BASE ; 
 int /*<<< orphan*/  EEPROM_MAC_ADDR_0 ; 
 int EEPROM_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  PCI_EEPROM_WIDTH_93C46 ; 
 int /*<<< orphan*/  PCI_EEPROM_WIDTH_93C66 ; 
 int /*<<< orphan*/  eeprom_93cx6_multiread (struct eeprom_93cx6*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2400pci_eepromregister_read ; 
 int /*<<< orphan*/  rt2400pci_eepromregister_write ; 
 int /*<<< orphan*/ * rt2x00_eeprom_addr (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 scalar_t__ rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00lib_set_mac_address (struct rt2x00_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2400pci_validate_eeprom(struct rt2x00_dev *rt2x00dev)
{
	struct eeprom_93cx6 eeprom;
	u32 reg;
	u16 word;
	u8 *mac;

	reg = rt2x00mmio_register_read(rt2x00dev, CSR21);

	eeprom.data = rt2x00dev;
	eeprom.register_read = rt2400pci_eepromregister_read;
	eeprom.register_write = rt2400pci_eepromregister_write;
	eeprom.width = rt2x00_get_field32(reg, CSR21_TYPE_93C46) ?
	    PCI_EEPROM_WIDTH_93C46 : PCI_EEPROM_WIDTH_93C66;
	eeprom.reg_data_in = 0;
	eeprom.reg_data_out = 0;
	eeprom.reg_data_clock = 0;
	eeprom.reg_chip_select = 0;

	eeprom_93cx6_multiread(&eeprom, EEPROM_BASE, rt2x00dev->eeprom,
			       EEPROM_SIZE / sizeof(u16));

	/*
	 * Start validation of the data that has been read.
	 */
	mac = rt2x00_eeprom_addr(rt2x00dev, EEPROM_MAC_ADDR_0);
	rt2x00lib_set_mac_address(rt2x00dev, mac);

	word = rt2x00_eeprom_read(rt2x00dev, EEPROM_ANTENNA);
	if (word == 0xffff) {
		rt2x00_err(rt2x00dev, "Invalid EEPROM data detected\n");
		return -EINVAL;
	}

	return 0;
}