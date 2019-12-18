#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union i2c_smbus_data {int dummy; } i2c_smbus_data ;
struct saa7146_dev {scalar_t__ revision; struct hexium* ext_priv; TYPE_1__* pci; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct hexium {TYPE_2__ i2c_adapter; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD1_INIT ; 
 int /*<<< orphan*/  DD1_STREAM_B ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int /*<<< orphan*/  DEB_S (char*) ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HEXIUM_HV_PCI6_ORION ; 
 int /*<<< orphan*/  HEXIUM_ORION_1SVHS_3BNC ; 
 int /*<<< orphan*/  HEXIUM_ORION_4BNC ; 
 int /*<<< orphan*/  I2C_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int MASK_08 ; 
 int MASK_09 ; 
 int MASK_10 ; 
 int MASK_24 ; 
 int MASK_25 ; 
 int MASK_26 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  MC2 ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTHI ; 
 int /*<<< orphan*/  SAA7146_I2C_BUS_BIT_RATE_480 ; 
 scalar_t__ i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_2__*) ; 
 int i2c_smbus_xfer (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 
 int /*<<< orphan*/  kfree (struct hexium*) ; 
 struct hexium* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  saa7146_i2c_adapter_prepare (struct saa7146_dev*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int hexium_probe(struct saa7146_dev *dev)
{
	struct hexium *hexium = NULL;
	union i2c_smbus_data data;
	int err = 0;

	DEB_EE("\n");

	/* there are no hexium orion cards with revision 0 saa7146s */
	if (0 == dev->revision) {
		return -EFAULT;
	}

	hexium = kzalloc(sizeof(*hexium), GFP_KERNEL);
	if (!hexium)
		return -ENOMEM;

	/* enable i2c-port pins */
	saa7146_write(dev, MC1, (MASK_08 | MASK_24 | MASK_10 | MASK_26));

	saa7146_write(dev, DD1_INIT, 0x01000100);
	saa7146_write(dev, DD1_STREAM_B, 0x00000000);
	saa7146_write(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	strscpy(hexium->i2c_adapter.name, "hexium orion",
		sizeof(hexium->i2c_adapter.name));
	saa7146_i2c_adapter_prepare(dev, &hexium->i2c_adapter, SAA7146_I2C_BUS_BIT_RATE_480);
	if (i2c_add_adapter(&hexium->i2c_adapter) < 0) {
		DEB_S("cannot register i2c-device. skipping.\n");
		kfree(hexium);
		return -EFAULT;
	}

	/* set SAA7110 control GPIO 0 */
	saa7146_setgpio(dev, 0, SAA7146_GPIO_OUTHI);
	/*  set HWControl GPIO number 2 */
	saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTHI);

	mdelay(10);

	/* detect newer Hexium Orion cards by subsystem ids */
	if (0x17c8 == dev->pci->subsystem_vendor && 0x0101 == dev->pci->subsystem_device) {
		pr_info("device is a Hexium Orion w/ 1 SVHS + 3 BNC inputs\n");
		/* we store the pointer in our private data field */
		dev->ext_priv = hexium;
		hexium->type = HEXIUM_ORION_1SVHS_3BNC;
		return 0;
	}

	if (0x17c8 == dev->pci->subsystem_vendor && 0x2101 == dev->pci->subsystem_device) {
		pr_info("device is a Hexium Orion w/ 4 BNC inputs\n");
		/* we store the pointer in our private data field */
		dev->ext_priv = hexium;
		hexium->type = HEXIUM_ORION_4BNC;
		return 0;
	}

	/* check if this is an old hexium Orion card by looking at
	   a saa7110 at address 0x4e */
	err = i2c_smbus_xfer(&hexium->i2c_adapter, 0x4e, 0, I2C_SMBUS_READ,
			     0x00, I2C_SMBUS_BYTE_DATA, &data);
	if (err == 0) {
		pr_info("device is a Hexium HV-PCI6/Orion (old)\n");
		/* we store the pointer in our private data field */
		dev->ext_priv = hexium;
		hexium->type = HEXIUM_HV_PCI6_ORION;
		return 0;
	}

	i2c_del_adapter(&hexium->i2c_adapter);
	kfree(hexium);
	return -EFAULT;
}