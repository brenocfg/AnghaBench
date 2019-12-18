#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; int /*<<< orphan*/ * key; } ;
struct TYPE_8__ {int /*<<< orphan*/ * private; TYPE_1__ attr; int /*<<< orphan*/  size; } ;
struct nvmem_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; TYPE_2__ eeprom; scalar_t__ base_dev; int /*<<< orphan*/  size; scalar_t__ read_only; } ;
struct nvmem_config {scalar_t__ base_dev; scalar_t__ root_only; int /*<<< orphan*/  compat; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLAG_COMPAT ; 
 TYPE_2__ bin_attr_ro_nvmem ; 
 TYPE_2__ bin_attr_ro_root_nvmem ; 
 TYPE_2__ bin_attr_rw_nvmem ; 
 TYPE_2__ bin_attr_rw_root_nvmem ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_create_bin_file (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  eeprom_lock_key ; 

int nvmem_sysfs_setup_compat(struct nvmem_device *nvmem,
			      const struct nvmem_config *config)
{
	int rval;

	if (!config->compat)
		return 0;

	if (!config->base_dev)
		return -EINVAL;

	if (nvmem->read_only) {
		if (config->root_only)
			nvmem->eeprom = bin_attr_ro_root_nvmem;
		else
			nvmem->eeprom = bin_attr_ro_nvmem;
	} else {
		if (config->root_only)
			nvmem->eeprom = bin_attr_rw_root_nvmem;
		else
			nvmem->eeprom = bin_attr_rw_nvmem;
	}
	nvmem->eeprom.attr.name = "eeprom";
	nvmem->eeprom.size = nvmem->size;
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	nvmem->eeprom.attr.key = &eeprom_lock_key;
#endif
	nvmem->eeprom.private = &nvmem->dev;
	nvmem->base_dev = config->base_dev;

	rval = device_create_bin_file(nvmem->base_dev, &nvmem->eeprom);
	if (rval) {
		dev_err(&nvmem->dev,
			"Failed to create eeprom binary file %d\n", rval);
		return rval;
	}

	nvmem->flags |= FLAG_COMPAT;

	return 0;
}