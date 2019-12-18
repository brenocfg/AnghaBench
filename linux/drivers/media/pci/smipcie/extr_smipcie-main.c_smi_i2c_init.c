#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct smi_dev {TYPE_4__* i2c_bus; TYPE_3__* i2c_bit; TYPE_2__* pci_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {TYPE_3__* algo_data; TYPE_1__ dev; void* owner; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int udelay; int timeout; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  (* setscl ) (struct smi_dev*,int) ;int /*<<< orphan*/  (* setsda ) (struct smi_dev*,int) ;struct smi_dev* data; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_A_SW_CTL ; 
 int /*<<< orphan*/  I2C_B_SW_CTL ; 
 void* THIS_MODULE ; 
 int i2c_bit_add_bus (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,struct smi_dev*) ; 
 int /*<<< orphan*/  smi_i2c0_getscl ; 
 int /*<<< orphan*/  smi_i2c0_getsda ; 
 int /*<<< orphan*/  smi_i2c0_setscl (struct smi_dev*,int) ; 
 int /*<<< orphan*/  smi_i2c0_setsda (struct smi_dev*,int) ; 
 int /*<<< orphan*/  smi_i2c1_getscl ; 
 int /*<<< orphan*/  smi_i2c1_getsda ; 
 int /*<<< orphan*/  smi_i2c1_setscl (struct smi_dev*,int) ; 
 int /*<<< orphan*/  smi_i2c1_setsda (struct smi_dev*,int) ; 
 int /*<<< orphan*/  smi_i2c_cfg (struct smi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int smi_i2c_init(struct smi_dev *dev)
{
	int ret;

	/* i2c bus 0 */
	smi_i2c_cfg(dev, I2C_A_SW_CTL);
	i2c_set_adapdata(&dev->i2c_bus[0], dev);
	strscpy(dev->i2c_bus[0].name, "SMI-I2C0", sizeof(dev->i2c_bus[0].name));
	dev->i2c_bus[0].owner = THIS_MODULE;
	dev->i2c_bus[0].dev.parent = &dev->pci_dev->dev;
	dev->i2c_bus[0].algo_data = &dev->i2c_bit[0];
	dev->i2c_bit[0].data = dev;
	dev->i2c_bit[0].setsda = smi_i2c0_setsda;
	dev->i2c_bit[0].setscl = smi_i2c0_setscl;
	dev->i2c_bit[0].getsda = smi_i2c0_getsda;
	dev->i2c_bit[0].getscl = smi_i2c0_getscl;
	dev->i2c_bit[0].udelay = 12;
	dev->i2c_bit[0].timeout = 10;
	/* Raise SCL and SDA */
	smi_i2c0_setsda(dev, 1);
	smi_i2c0_setscl(dev, 1);

	ret = i2c_bit_add_bus(&dev->i2c_bus[0]);
	if (ret < 0)
		return ret;

	/* i2c bus 1 */
	smi_i2c_cfg(dev, I2C_B_SW_CTL);
	i2c_set_adapdata(&dev->i2c_bus[1], dev);
	strscpy(dev->i2c_bus[1].name, "SMI-I2C1", sizeof(dev->i2c_bus[1].name));
	dev->i2c_bus[1].owner = THIS_MODULE;
	dev->i2c_bus[1].dev.parent = &dev->pci_dev->dev;
	dev->i2c_bus[1].algo_data = &dev->i2c_bit[1];
	dev->i2c_bit[1].data = dev;
	dev->i2c_bit[1].setsda = smi_i2c1_setsda;
	dev->i2c_bit[1].setscl = smi_i2c1_setscl;
	dev->i2c_bit[1].getsda = smi_i2c1_getsda;
	dev->i2c_bit[1].getscl = smi_i2c1_getscl;
	dev->i2c_bit[1].udelay = 12;
	dev->i2c_bit[1].timeout = 10;
	/* Raise SCL and SDA */
	smi_i2c1_setsda(dev, 1);
	smi_i2c1_setscl(dev, 1);

	ret = i2c_bit_add_bus(&dev->i2c_bus[1]);
	if (ret < 0)
		i2c_del_adapter(&dev->i2c_bus[0]);

	return ret;
}