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
struct occ {int /*<<< orphan*/  bus_dev; int /*<<< orphan*/  hwmon; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  group; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ESHUTDOWN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_hwmon_device_register_with_groups (int /*<<< orphan*/ ,char const*,struct occ*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  occ_parse_poll_response (struct occ*) ; 
 int occ_poll (struct occ*) ; 
 int occ_setup_sensor_attrs (struct occ*) ; 
 int occ_setup_sysfs (struct occ*) ; 

int occ_setup(struct occ *occ, const char *name)
{
	int rc;

	mutex_init(&occ->lock);
	occ->groups[0] = &occ->group;

	/* no need to lock */
	rc = occ_poll(occ);
	if (rc == -ESHUTDOWN) {
		dev_info(occ->bus_dev, "host is not ready\n");
		return rc;
	} else if (rc < 0) {
		dev_err(occ->bus_dev, "failed to get OCC poll response: %d\n",
			rc);
		return rc;
	}

	occ_parse_poll_response(occ);

	rc = occ_setup_sensor_attrs(occ);
	if (rc) {
		dev_err(occ->bus_dev, "failed to setup sensor attrs: %d\n",
			rc);
		return rc;
	}

	occ->hwmon = devm_hwmon_device_register_with_groups(occ->bus_dev, name,
							    occ, occ->groups);
	if (IS_ERR(occ->hwmon)) {
		rc = PTR_ERR(occ->hwmon);
		dev_err(occ->bus_dev, "failed to register hwmon device: %d\n",
			rc);
		return rc;
	}

	rc = occ_setup_sysfs(occ);
	if (rc)
		dev_err(occ->bus_dev, "failed to setup sysfs: %d\n", rc);

	return rc;
}