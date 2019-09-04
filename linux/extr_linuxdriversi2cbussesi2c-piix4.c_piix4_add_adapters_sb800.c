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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct i2c_piix4_adapdata {scalar_t__ smba; } ;

/* Variables and functions */
 int PIIX4_MAX_ADAPTERS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_del_adapter (struct i2c_piix4_adapdata*) ; 
 struct i2c_piix4_adapdata* i2c_get_adapdata (struct i2c_piix4_adapdata*) ; 
 int /*<<< orphan*/  kfree (struct i2c_piix4_adapdata*) ; 
 int piix4_add_adapter (struct pci_dev*,unsigned short,int,int,int,int /*<<< orphan*/ ,struct i2c_piix4_adapdata**) ; 
 struct i2c_piix4_adapdata** piix4_main_adapters ; 
 int /*<<< orphan*/ * piix4_main_port_names_sb800 ; 

__attribute__((used)) static int piix4_add_adapters_sb800(struct pci_dev *dev, unsigned short smba,
				    bool notify_imc)
{
	struct i2c_piix4_adapdata *adapdata;
	int port;
	int retval;

	for (port = 0; port < PIIX4_MAX_ADAPTERS; port++) {
		retval = piix4_add_adapter(dev, smba, true, port, notify_imc,
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