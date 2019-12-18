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
struct dasd_device {scalar_t__ state; int features; TYPE_3__* block; TYPE_2__* discipline; int /*<<< orphan*/  flags; TYPE_1__* cdev; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int fmode_t ;
struct TYPE_6__ {int /*<<< orphan*/  open_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DASD_FEATURE_READONLY ; 
 int /*<<< orphan*/  DASD_FLAG_DEVICE_RO ; 
 int /*<<< orphan*/  DASD_FLAG_OFFLINE ; 
 scalar_t__ DASD_STATE_BASIC ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 int EROFS ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct dasd_device* dasd_device_from_gendisk (int /*<<< orphan*/ ) ; 
 scalar_t__ dasd_probeonly ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dasd_open(struct block_device *bdev, fmode_t mode)
{
	struct dasd_device *base;
	int rc;

	base = dasd_device_from_gendisk(bdev->bd_disk);
	if (!base)
		return -ENODEV;

	atomic_inc(&base->block->open_count);
	if (test_bit(DASD_FLAG_OFFLINE, &base->flags)) {
		rc = -ENODEV;
		goto unlock;
	}

	if (!try_module_get(base->discipline->owner)) {
		rc = -EINVAL;
		goto unlock;
	}

	if (dasd_probeonly) {
		dev_info(&base->cdev->dev,
			 "Accessing the DASD failed because it is in "
			 "probeonly mode\n");
		rc = -EPERM;
		goto out;
	}

	if (base->state <= DASD_STATE_BASIC) {
		DBF_DEV_EVENT(DBF_ERR, base, " %s",
			      " Cannot open unrecognized device");
		rc = -ENODEV;
		goto out;
	}

	if ((mode & FMODE_WRITE) &&
	    (test_bit(DASD_FLAG_DEVICE_RO, &base->flags) ||
	     (base->features & DASD_FEATURE_READONLY))) {
		rc = -EROFS;
		goto out;
	}

	dasd_put_device(base);
	return 0;

out:
	module_put(base->discipline->owner);
unlock:
	atomic_dec(&base->block->open_count);
	dasd_put_device(base);
	return rc;
}