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
struct via_port_cfg {int ioport_index; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct i2c_algo_bit_data {int udelay; int timeout; struct via_port_cfg* data; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  (* setscl ) (struct via_port_cfg*,int) ;int /*<<< orphan*/  (* setsda ) (struct via_port_cfg*,int) ;} ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {TYPE_1__ dev; struct i2c_algo_bit_data* algo_data; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int i2c_bit_add_bus (struct i2c_adapter*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  via_i2c_getscl ; 
 int /*<<< orphan*/  via_i2c_getsda ; 
 int /*<<< orphan*/  via_i2c_setscl (struct via_port_cfg*,int) ; 
 int /*<<< orphan*/  via_i2c_setsda (struct via_port_cfg*,int) ; 

__attribute__((used)) static int create_i2c_bus(struct i2c_adapter *adapter,
			  struct i2c_algo_bit_data *algo,
			  struct via_port_cfg *adap_cfg,
			  struct pci_dev *pdev)
{
	algo->setsda = via_i2c_setsda;
	algo->setscl = via_i2c_setscl;
	algo->getsda = via_i2c_getsda;
	algo->getscl = via_i2c_getscl;
	algo->udelay = 10;
	algo->timeout = 2;
	algo->data = adap_cfg;

	sprintf(adapter->name, "viafb i2c io_port idx 0x%02x",
		adap_cfg->ioport_index);
	adapter->owner = THIS_MODULE;
	adapter->class = I2C_CLASS_DDC;
	adapter->algo_data = algo;
	if (pdev)
		adapter->dev.parent = &pdev->dev;
	else
		adapter->dev.parent = NULL;
	/* i2c_set_adapdata(adapter, adap_cfg); */

	/* Raise SCL and SDA */
	via_i2c_setsda(adap_cfg, 1);
	via_i2c_setscl(adap_cfg, 1);
	udelay(20);

	return i2c_bit_add_bus(adapter);
}