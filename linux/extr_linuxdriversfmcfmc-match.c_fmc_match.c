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
struct fmc_fru_id {scalar_t__ product_name; scalar_t__ manufacturer; } ;
struct TYPE_3__ {int fru_id_nr; struct fmc_fru_id* fru_id; } ;
struct fmc_driver {TYPE_1__ id_table; } ;
struct TYPE_4__ {int /*<<< orphan*/  product_name; int /*<<< orphan*/  manufacturer; } ;
struct fmc_device {TYPE_2__ id; int /*<<< orphan*/  dev; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 struct fmc_device* to_fmc_device (struct device*) ; 
 struct fmc_driver* to_fmc_driver (struct device_driver*) ; 

int fmc_match(struct device *dev, struct device_driver *drv)
{
	struct fmc_driver *fdrv = to_fmc_driver(drv);
	struct fmc_device *fdev = to_fmc_device(dev);
	struct fmc_fru_id *fid;
	int i, matched = 0;

	/* This currently only matches the EEPROM (FRU id) */
	fid = fdrv->id_table.fru_id;
	if (!fid) {
		dev_warn(&fdev->dev, "Driver has no ID: matches all\n");
		matched = 1;
	} else {
		if (!fdev->id.manufacturer || !fdev->id.product_name)
			return 0; /* the device has no FRU information */
		for (i = 0; i < fdrv->id_table.fru_id_nr; i++, fid++) {
			if (fid->manufacturer &&
			    strcmp(fid->manufacturer, fdev->id.manufacturer))
				continue;
			if (fid->product_name &&
			    strcmp(fid->product_name, fdev->id.product_name))
				continue;
			matched = 1;
			break;
		}
	}

	/* FIXME: match SDB contents */
	return matched;
}