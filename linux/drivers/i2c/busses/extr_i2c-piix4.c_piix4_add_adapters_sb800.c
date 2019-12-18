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
typedef  int u8 ;
struct pci_dev {scalar_t__ device; int revision; int /*<<< orphan*/  dev; } ;
struct i2c_piix4_adapdata {scalar_t__ smba; } ;

/* Variables and functions */
 int HUDSON2_MAIN_PORTS ; 
 scalar_t__ PCI_DEVICE_ID_AMD_HUDSON2_SMBUS ; 
 scalar_t__ PCI_DEVICE_ID_AMD_KERNCZ_SMBUS ; 
 int PIIX4_MAX_ADAPTERS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_del_adapter (struct i2c_piix4_adapdata*) ; 
 struct i2c_piix4_adapdata* i2c_get_adapdata (struct i2c_piix4_adapdata*) ; 
 int /*<<< orphan*/  kfree (struct i2c_piix4_adapdata*) ; 
 int piix4_adapter_count ; 
 int piix4_add_adapter (struct pci_dev*,unsigned short,int,int,int,int,int /*<<< orphan*/ ,struct i2c_piix4_adapdata**) ; 
 struct i2c_piix4_adapdata** piix4_main_adapters ; 
 int /*<<< orphan*/ * piix4_main_port_names_sb800 ; 

__attribute__((used)) static int piix4_add_adapters_sb800(struct pci_dev *dev, unsigned short smba,
				    bool notify_imc)
{
	struct i2c_piix4_adapdata *adapdata;
	int port;
	int retval;

	if (dev->device == PCI_DEVICE_ID_AMD_KERNCZ_SMBUS ||
	    (dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS &&
	     dev->revision >= 0x1F)) {
		piix4_adapter_count = HUDSON2_MAIN_PORTS;
	} else {
		piix4_adapter_count = PIIX4_MAX_ADAPTERS;
	}

	for (port = 0; port < piix4_adapter_count; port++) {
		u8 hw_port_nr = port == 0 ? 0 : port + 1;

		retval = piix4_add_adapter(dev, smba, true, port, notify_imc,
					   hw_port_nr,
					   piix4_main_port_names_sb800[port],
					   &piix4_main_adapters[port]);
		if (retval < 0)
			goto error;
	}

	return retval;

error:
	dev_err(&dev->dev,
		"Error setting up SB800 adapters. Unregistering!\n");
	while (--port >= 0) {
		adapdata = i2c_get_adapdata(piix4_main_adapters[port]);
		if (adapdata->smba) {
			i2c_del_adapter(piix4_main_adapters[port]);
			kfree(adapdata);
			kfree(piix4_main_adapters[port]);
			piix4_main_adapters[port] = NULL;
		}
	}

	return retval;
}