#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct zfcp_unit {int /*<<< orphan*/  list; TYPE_1__ dev; int /*<<< orphan*/  scsi_work; scalar_t__ fcp_lun; struct zfcp_port* port; } ;
struct zfcp_port {int /*<<< orphan*/  unit_list_lock; int /*<<< orphan*/  unit_list; int /*<<< orphan*/  units; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ dev_set_name (TYPE_1__*,char*,unsigned long long) ; 
 scalar_t__ device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct zfcp_unit*) ; 
 struct zfcp_unit* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ zfcp_sysfs_port_is_removing (struct zfcp_port*) ; 
 int /*<<< orphan*/  zfcp_sysfs_port_units_mutex ; 
 int /*<<< orphan*/  zfcp_unit_attr_groups ; 
 struct zfcp_unit* zfcp_unit_find (struct zfcp_port*,scalar_t__) ; 
 int /*<<< orphan*/  zfcp_unit_release ; 
 int /*<<< orphan*/  zfcp_unit_scsi_scan (struct zfcp_unit*) ; 
 int /*<<< orphan*/  zfcp_unit_scsi_scan_work ; 

int zfcp_unit_add(struct zfcp_port *port, u64 fcp_lun)
{
	struct zfcp_unit *unit;
	int retval = 0;

	mutex_lock(&zfcp_sysfs_port_units_mutex);
	if (zfcp_sysfs_port_is_removing(port)) {
		/* port is already gone */
		retval = -ENODEV;
		goto out;
	}

	unit = zfcp_unit_find(port, fcp_lun);
	if (unit) {
		put_device(&unit->dev);
		retval = -EEXIST;
		goto out;
	}

	unit = kzalloc(sizeof(struct zfcp_unit), GFP_KERNEL);
	if (!unit) {
		retval = -ENOMEM;
		goto out;
	}

	unit->port = port;
	unit->fcp_lun = fcp_lun;
	unit->dev.parent = &port->dev;
	unit->dev.release = zfcp_unit_release;
	unit->dev.groups = zfcp_unit_attr_groups;
	INIT_WORK(&unit->scsi_work, zfcp_unit_scsi_scan_work);

	if (dev_set_name(&unit->dev, "0x%016llx",
			 (unsigned long long) fcp_lun)) {
		kfree(unit);
		retval = -ENOMEM;
		goto out;
	}

	if (device_register(&unit->dev)) {
		put_device(&unit->dev);
		retval = -ENOMEM;
		goto out;
	}

	atomic_inc(&port->units); /* under zfcp_sysfs_port_units_mutex ! */

	write_lock_irq(&port->unit_list_lock);
	list_add_tail(&unit->list, &port->unit_list);
	write_unlock_irq(&port->unit_list_lock);
	/*
	 * lock order: shost->scan_mutex before zfcp_sysfs_port_units_mutex
	 * due to      zfcp_unit_scsi_scan() => zfcp_scsi_slave_alloc()
	 */
	mutex_unlock(&zfcp_sysfs_port_units_mutex);

	zfcp_unit_scsi_scan(unit);
	return retval;

out:
	mutex_unlock(&zfcp_sysfs_port_units_mutex);
	return retval;
}