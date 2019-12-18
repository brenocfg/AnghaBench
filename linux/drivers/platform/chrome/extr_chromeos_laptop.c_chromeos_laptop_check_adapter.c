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
struct i2c_peripheral {size_t type; int /*<<< orphan*/  alt_addr; int /*<<< orphan*/  board_info; scalar_t__ client; scalar_t__ pci_devid; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct i2c_adapter {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int num_i2c_peripherals; struct i2c_peripheral* i2c_peripherals; } ;

/* Variables and functions */
 int /*<<< orphan*/  chromeos_laptop_match_adapter_devid (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ chromes_laptop_instantiate_i2c_device (struct i2c_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* cros_laptop ; 
 int /*<<< orphan*/ * i2c_adapter_names ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chromeos_laptop_check_adapter(struct i2c_adapter *adapter)
{
	struct i2c_peripheral *i2c_dev;
	int i;

	for (i = 0; i < cros_laptop->num_i2c_peripherals; i++) {
		i2c_dev = &cros_laptop->i2c_peripherals[i];

		/* Skip devices already created */
		if (i2c_dev->client)
			continue;

		if (strncmp(adapter->name, i2c_adapter_names[i2c_dev->type],
			    strlen(i2c_adapter_names[i2c_dev->type])))
			continue;

		if (i2c_dev->pci_devid &&
		    !chromeos_laptop_match_adapter_devid(adapter->dev.parent,
							 i2c_dev->pci_devid)) {
			continue;
		}

		i2c_dev->client =
			chromes_laptop_instantiate_i2c_device(adapter,
							&i2c_dev->board_info,
							i2c_dev->alt_addr);
	}
}