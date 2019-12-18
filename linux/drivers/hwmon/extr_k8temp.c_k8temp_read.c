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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct k8temp_data {int swap_core_select; long temp_offset; int /*<<< orphan*/  update_lock; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TEMP ; 
 int SEL_CORE ; 
 int SEL_PLACE ; 
 long TEMP_FROM_REG (int /*<<< orphan*/ ) ; 
 struct k8temp_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
k8temp_read(struct device *dev, enum hwmon_sensor_types type,
	    u32 attr, int channel, long *val)
{
	struct k8temp_data *data = dev_get_drvdata(dev);
	struct pci_dev *pdev = to_pci_dev(dev->parent);
	int core, place;
	u32 temp;
	u8 tmp;

	core = (channel >> 1) & 1;
	place = channel & 1;

	core ^= data->swap_core_select;

	mutex_lock(&data->update_lock);
	pci_read_config_byte(pdev, REG_TEMP, &tmp);
	tmp &= ~(SEL_PLACE | SEL_CORE);
	if (core)
		tmp |= SEL_CORE;
	if (place)
		tmp |= SEL_PLACE;
	pci_write_config_byte(pdev, REG_TEMP, tmp);
	pci_read_config_dword(pdev, REG_TEMP, &temp);
	mutex_unlock(&data->update_lock);

	*val = TEMP_FROM_REG(temp) + data->temp_offset;

	return 0;
}