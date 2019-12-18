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
struct pqi_scsi_dev {int keep_device; int /*<<< orphan*/  scsi_device_list_entry; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  scsi_device_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void pqi_fixup_botched_add(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device)
{
	unsigned long flags;

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);
	list_del(&device->scsi_device_list_entry);
	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	/* Allow the device structure to be freed later. */
	device->keep_device = false;
}