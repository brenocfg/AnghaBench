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
struct fmc_driver {int dummy; } ;
struct fmc_device {int /*<<< orphan*/  dev; TYPE_1__* op; } ;
struct TYPE_2__ {int (* reprogram ) (struct fmc_device*,struct fmc_driver*,char*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int fmc_scan_sdb_tree (struct fmc_device*,int) ; 
 int stub1 (struct fmc_device*,struct fmc_driver*,char*) ; 

int fmc_reprogram(struct fmc_device *fmc, struct fmc_driver *d, char *gw,
			 int sdb_entry)
{
	int ret;

	ret = fmc->op->reprogram(fmc, d, gw);
	if (ret < 0)
		return ret;
	if (sdb_entry < 0)
		return ret;

	/* We are required to find SDB at a given offset */
	ret = fmc_scan_sdb_tree(fmc, sdb_entry);
	if (ret < 0) {
		dev_err(&fmc->dev, "Can't find SDB at address 0x%x\n",
			sdb_entry);
		return -ENODEV;
	}

	return 0;
}