#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_7__ {int /*<<< orphan*/  shost; } ;
struct sas_ha_struct {int /*<<< orphan*/  lock; TYPE_3__ core; int /*<<< orphan*/  eh_dev_q; int /*<<< orphan*/  eh_active; } ;
struct TYPE_6__ {int /*<<< orphan*/  reset_lun; int /*<<< orphan*/  eh_list_node; } ;
struct domain_device {TYPE_4__* rphy; TYPE_2__ ssp_dev; int /*<<< orphan*/  state; TYPE_1__* port; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct sas_ha_struct* ha; } ;

/* Variables and functions */
 int FAILED ; 
 int SAS_DEV_EH_PENDING ; 
 int SAS_DEV_LU_RESET ; 
 int SUCCESS ; 
 scalar_t__ dev_is_sata (struct domain_device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_ata_schedule_reset (struct domain_device*) ; 
 int /*<<< orphan*/  sas_ata_wait_eh (struct domain_device*) ; 
 int /*<<< orphan*/  sas_wait_eh (struct domain_device*) ; 
 int /*<<< orphan*/  scsi_schedule_eh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sas_queue_reset(struct domain_device *dev, int reset_type,
			   u64 lun, int wait)
{
	struct sas_ha_struct *ha = dev->port->ha;
	int scheduled = 0, tries = 100;

	/* ata: promote lun reset to bus reset */
	if (dev_is_sata(dev)) {
		sas_ata_schedule_reset(dev);
		if (wait)
			sas_ata_wait_eh(dev);
		return SUCCESS;
	}

	while (!scheduled && tries--) {
		spin_lock_irq(&ha->lock);
		if (!test_bit(SAS_DEV_EH_PENDING, &dev->state) &&
		    !test_bit(reset_type, &dev->state)) {
			scheduled = 1;
			ha->eh_active++;
			list_add_tail(&dev->ssp_dev.eh_list_node, &ha->eh_dev_q);
			set_bit(SAS_DEV_EH_PENDING, &dev->state);
			set_bit(reset_type, &dev->state);
			int_to_scsilun(lun, &dev->ssp_dev.reset_lun);
			scsi_schedule_eh(ha->core.shost);
		}
		spin_unlock_irq(&ha->lock);

		if (wait)
			sas_wait_eh(dev);

		if (scheduled)
			return SUCCESS;
	}

	pr_warn("%s reset of %s failed\n",
		reset_type == SAS_DEV_LU_RESET ? "LUN" : "Bus",
		dev_name(&dev->rphy->dev));

	return FAILED;
}