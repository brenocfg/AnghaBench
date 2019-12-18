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
struct sas_phy_data {int reset_result; int hard_reset; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  reset_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct sas_phy {struct sas_phy_data* hostdata; TYPE_1__ dev; } ;
struct sas_ha_struct {int /*<<< orphan*/  lock; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sas_drain_work (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  sas_queue_work (struct sas_ha_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int queue_phy_reset(struct sas_phy *phy, int hard_reset)
{
	struct Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	struct sas_ha_struct *ha = SHOST_TO_SAS_HA(shost);
	struct sas_phy_data *d = phy->hostdata;
	int rc;

	if (!d)
		return -ENOMEM;

	/* libsas workqueue coordinates ata-eh reset with discovery */
	mutex_lock(&d->event_lock);
	d->reset_result = 0;
	d->hard_reset = hard_reset;

	spin_lock_irq(&ha->lock);
	sas_queue_work(ha, &d->reset_work);
	spin_unlock_irq(&ha->lock);

	rc = sas_drain_work(ha);
	if (rc == 0)
		rc = d->reset_result;
	mutex_unlock(&d->event_lock);

	return rc;
}