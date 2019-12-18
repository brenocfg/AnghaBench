#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct i2c_adapter {int dummy; } ;
struct ngene_channel {scalar_t__ number; struct i2c_adapter i2c_adapter; TYPE_2__* dev; } ;
struct device {int dummy; } ;
typedef  scalar_t__ s16 ;
struct TYPE_4__ {TYPE_1__* pci_dev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__) ; 
 scalar_t__ eeprom_read_ushort (struct i2c_adapter*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  eeprom_write_ushort (struct i2c_adapter*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static s16 osc_deviation(void *priv, s16 deviation, int flag)
{
	struct ngene_channel *chan = priv;
	struct device *pdev = &chan->dev->pci_dev->dev;
	struct i2c_adapter *adap = &chan->i2c_adapter;
	u16 data = 0;

	if (flag) {
		data = (u16) deviation;
		dev_info(pdev, "write deviation %d\n",
			 deviation);
		eeprom_write_ushort(adap, 0x1000 + chan->number, data);
	} else {
		if (eeprom_read_ushort(adap, 0x1000 + chan->number, &data))
			data = 0;
		dev_info(pdev, "read deviation %d\n",
			 (s16)data);
	}

	return (s16) data;
}