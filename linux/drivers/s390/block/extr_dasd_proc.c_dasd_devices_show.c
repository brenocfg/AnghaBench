#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct dasd_device {int features; int state; TYPE_2__* discipline; TYPE_1__* cdev; struct dasd_block* block; } ;
struct dasd_block {int bp_block; int blocks; TYPE_3__* gdp; } ;
struct TYPE_6__ {int /*<<< orphan*/  disk_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DASD_FEATURE_READONLY ; 
#define  DASD_STATE_BASIC 133 
#define  DASD_STATE_KNOWN 132 
#define  DASD_STATE_NEW 131 
#define  DASD_STATE_ONLINE 130 
#define  DASD_STATE_READY 129 
#define  DASD_STATE_UNFMT 128 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_check_blocksize (int) ; 
 struct dasd_device* dasd_device_from_devindex (unsigned long) ; 
 scalar_t__ dasd_probeonly ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disk_devt (TYPE_3__*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int
dasd_devices_show(struct seq_file *m, void *v)
{
	struct dasd_device *device;
	struct dasd_block *block;
	char *substr;

	device = dasd_device_from_devindex((unsigned long) v - 1);
	if (IS_ERR(device))
		return 0;
	if (device->block)
		block = device->block;
	else {
		dasd_put_device(device);
		return 0;
	}
	/* Print device number. */
	seq_printf(m, "%s", dev_name(&device->cdev->dev));
	/* Print discipline string. */
	if (device->discipline != NULL)
		seq_printf(m, "(%s)", device->discipline->name);
	else
		seq_printf(m, "(none)");
	/* Print kdev. */
	if (block->gdp)
		seq_printf(m, " at (%3d:%6d)",
			   MAJOR(disk_devt(block->gdp)),
			   MINOR(disk_devt(block->gdp)));
	else
		seq_printf(m, "  at (???:??????)");
	/* Print device name. */
	if (block->gdp)
		seq_printf(m, " is %-8s", block->gdp->disk_name);
	else
		seq_printf(m, " is ????????");
	/* Print devices features. */
	substr = (device->features & DASD_FEATURE_READONLY) ? "(ro)" : " ";
	seq_printf(m, "%4s: ", substr);
	/* Print device status information. */
	switch (device->state) {
	case DASD_STATE_NEW:
		seq_printf(m, "new");
		break;
	case DASD_STATE_KNOWN:
		seq_printf(m, "detected");
		break;
	case DASD_STATE_BASIC:
		seq_printf(m, "basic");
		break;
	case DASD_STATE_UNFMT:
		seq_printf(m, "unformatted");
		break;
	case DASD_STATE_READY:
	case DASD_STATE_ONLINE:
		seq_printf(m, "active ");
		if (dasd_check_blocksize(block->bp_block))
			seq_printf(m, "n/f	 ");
		else
			seq_printf(m,
				   "at blocksize: %u, %lu blocks, %lu MB",
				   block->bp_block, block->blocks,
				   ((block->bp_block >> 9) *
				    block->blocks) >> 11);
		break;
	default:
		seq_printf(m, "no stat");
		break;
	}
	dasd_put_device(device);
	if (dasd_probeonly)
		seq_printf(m, "(probeonly)");
	seq_printf(m, "\n");
	return 0;
}