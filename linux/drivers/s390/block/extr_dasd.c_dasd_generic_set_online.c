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
struct dasd_discipline {int (* check_device ) (struct dasd_device*) ;int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct dasd_device {int features; scalar_t__ state; scalar_t__ block; struct dasd_discipline* discipline; struct dasd_discipline* base_discipline; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_DIAG_MOD ; 
 int /*<<< orphan*/  DASD_FEATURE_INITIAL_ONLINE ; 
 int DASD_FEATURE_USEDIAG ; 
 scalar_t__ DASD_STATE_KNOWN ; 
 int /*<<< orphan*/  DASD_STATE_NEW ; 
 int /*<<< orphan*/  DASD_STATE_ONLINE ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int PTR_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  _wait_for_device (struct dasd_device*) ; 
 struct dasd_device* dasd_create_device (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_delete_device (struct dasd_device*) ; 
 struct dasd_discipline* dasd_diag_discipline_pointer ; 
 int /*<<< orphan*/  dasd_free_block (scalar_t__) ; 
 int /*<<< orphan*/  dasd_init_waitq ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_set_feature (struct ccw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_set_target_state (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int request_module (int /*<<< orphan*/ ) ; 
 int stub1 (struct dasd_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dasd_generic_set_online(struct ccw_device *cdev,
			    struct dasd_discipline *base_discipline)
{
	struct dasd_discipline *discipline;
	struct dasd_device *device;
	int rc;

	/* first online clears initial online feature flag */
	dasd_set_feature(cdev, DASD_FEATURE_INITIAL_ONLINE, 0);
	device = dasd_create_device(cdev);
	if (IS_ERR(device))
		return PTR_ERR(device);

	discipline = base_discipline;
	if (device->features & DASD_FEATURE_USEDIAG) {
	  	if (!dasd_diag_discipline_pointer) {
			/* Try to load the required module. */
			rc = request_module(DASD_DIAG_MOD);
			if (rc) {
				pr_warn("%s Setting the DASD online failed "
					"because the required module %s "
					"could not be loaded (rc=%d)\n",
					dev_name(&cdev->dev), DASD_DIAG_MOD,
					rc);
				dasd_delete_device(device);
				return -ENODEV;
			}
		}
		/* Module init could have failed, so check again here after
		 * request_module(). */
		if (!dasd_diag_discipline_pointer) {
			pr_warn("%s Setting the DASD online failed because of missing DIAG discipline\n",
				dev_name(&cdev->dev));
			dasd_delete_device(device);
			return -ENODEV;
		}
		discipline = dasd_diag_discipline_pointer;
	}
	if (!try_module_get(base_discipline->owner)) {
		dasd_delete_device(device);
		return -EINVAL;
	}
	if (!try_module_get(discipline->owner)) {
		module_put(base_discipline->owner);
		dasd_delete_device(device);
		return -EINVAL;
	}
	device->base_discipline = base_discipline;
	device->discipline = discipline;

	/* check_device will allocate block device if necessary */
	rc = discipline->check_device(device);
	if (rc) {
		pr_warn("%s Setting the DASD online with discipline %s failed with rc=%i\n",
			dev_name(&cdev->dev), discipline->name, rc);
		module_put(discipline->owner);
		module_put(base_discipline->owner);
		dasd_delete_device(device);
		return rc;
	}

	dasd_set_target_state(device, DASD_STATE_ONLINE);
	if (device->state <= DASD_STATE_KNOWN) {
		pr_warn("%s Setting the DASD online failed because of a missing discipline\n",
			dev_name(&cdev->dev));
		rc = -ENODEV;
		dasd_set_target_state(device, DASD_STATE_NEW);
		if (device->block)
			dasd_free_block(device->block);
		dasd_delete_device(device);
	} else
		pr_debug("dasd_generic device %s found\n",
				dev_name(&cdev->dev));

	wait_event(dasd_init_waitq, _wait_for_device(device));

	dasd_put_device(device);
	return rc;
}