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
struct TYPE_4__ {size_t real_unit_addr; scalar_t__ type; } ;
struct dasd_eckd_private {TYPE_1__ uid; struct alias_lcu* lcu; } ;
struct dasd_device {int /*<<< orphan*/  alias_list; struct dasd_eckd_private* private; } ;
struct alias_lcu {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  active_devices; TYPE_3__* uac; } ;
typedef  size_t __u8 ;
struct TYPE_6__ {TYPE_2__* unit; } ;
struct TYPE_5__ {scalar_t__ ua_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int UPDATE_PENDING ; 
 int _add_device_to_lcu (struct alias_lcu*,struct dasd_device*,struct dasd_device*) ; 
 int /*<<< orphan*/  _schedule_lcu_update (struct alias_lcu*,struct dasd_device*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dasd_alias_add_device(struct dasd_device *device)
{
	struct dasd_eckd_private *private = device->private;
	__u8 uaddr = private->uid.real_unit_addr;
	struct alias_lcu *lcu = private->lcu;
	unsigned long flags;
	int rc;

	rc = 0;
	spin_lock_irqsave(&lcu->lock, flags);
	/*
	 * Check if device and lcu type differ. If so, the uac data may be
	 * outdated and needs to be updated.
	 */
	if (private->uid.type !=  lcu->uac->unit[uaddr].ua_type) {
		lcu->flags |= UPDATE_PENDING;
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "uid type mismatch - trigger rescan");
	}
	if (!(lcu->flags & UPDATE_PENDING)) {
		rc = _add_device_to_lcu(lcu, device, device);
		if (rc)
			lcu->flags |= UPDATE_PENDING;
	}
	if (lcu->flags & UPDATE_PENDING) {
		list_move(&device->alias_list, &lcu->active_devices);
		_schedule_lcu_update(lcu, device);
	}
	spin_unlock_irqrestore(&lcu->lock, flags);
	return rc;
}