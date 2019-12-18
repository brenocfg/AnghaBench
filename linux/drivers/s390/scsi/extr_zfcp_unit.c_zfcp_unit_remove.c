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
typedef  int /*<<< orphan*/  u64 ;
struct zfcp_unit {int /*<<< orphan*/  dev; int /*<<< orphan*/  list; } ;
struct zfcp_port {int /*<<< orphan*/  unit_list_lock; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct zfcp_unit* _zfcp_unit_find (struct zfcp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_remove_device (struct scsi_device*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 struct scsi_device* zfcp_unit_sdev (struct zfcp_unit*) ; 

int zfcp_unit_remove(struct zfcp_port *port, u64 fcp_lun)
{
	struct zfcp_unit *unit;
	struct scsi_device *sdev;

	write_lock_irq(&port->unit_list_lock);
	unit = _zfcp_unit_find(port, fcp_lun);
	if (unit)
		list_del(&unit->list);
	write_unlock_irq(&port->unit_list_lock);

	if (!unit)
		return -EINVAL;

	sdev = zfcp_unit_sdev(unit);
	if (sdev) {
		scsi_remove_device(sdev);
		scsi_device_put(sdev);
	}

	put_device(&unit->dev);

	device_unregister(&unit->dev);

	return 0;
}