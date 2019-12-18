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
struct sas_phy {int dummy; } ;
struct pm8001_hba_info {int dummy; } ;
struct pm8001_device {int /*<<< orphan*/  device_id; } ;
struct domain_device {struct pm8001_device* lldd_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PM8001_EH_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int TMF_RESP_FUNC_FAILED ; 
 scalar_t__ dev_is_sata (struct domain_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pm8001_exec_internal_task_abort (struct pm8001_hba_info*,struct pm8001_device*,struct domain_device*,int,int /*<<< orphan*/ ) ; 
 struct pm8001_hba_info* pm8001_find_ha_by_dev (struct domain_device*) ; 
 int /*<<< orphan*/  pm8001_printk (char*,int /*<<< orphan*/ ,int) ; 
 struct sas_phy* sas_get_local_phy (struct domain_device*) ; 
 int sas_phy_reset (struct sas_phy*,int) ; 
 int /*<<< orphan*/  sas_put_local_phy (struct sas_phy*) ; 
 scalar_t__ scsi_is_sas_phy_local (struct sas_phy*) ; 

int pm8001_I_T_nexus_reset(struct domain_device *dev)
{
	int rc = TMF_RESP_FUNC_FAILED;
	struct pm8001_device *pm8001_dev;
	struct pm8001_hba_info *pm8001_ha;
	struct sas_phy *phy;

	if (!dev || !dev->lldd_dev)
		return -ENODEV;

	pm8001_dev = dev->lldd_dev;
	pm8001_ha = pm8001_find_ha_by_dev(dev);
	phy = sas_get_local_phy(dev);

	if (dev_is_sata(dev)) {
		if (scsi_is_sas_phy_local(phy)) {
			rc = 0;
			goto out;
		}
		rc = sas_phy_reset(phy, 1);
		if (rc) {
			PM8001_EH_DBG(pm8001_ha,
			pm8001_printk("phy reset failed for device %x\n"
			"with rc %d\n", pm8001_dev->device_id, rc));
			rc = TMF_RESP_FUNC_FAILED;
			goto out;
		}
		msleep(2000);
		rc = pm8001_exec_internal_task_abort(pm8001_ha, pm8001_dev ,
			dev, 1, 0);
		if (rc) {
			PM8001_EH_DBG(pm8001_ha,
			pm8001_printk("task abort failed %x\n"
			"with rc %d\n", pm8001_dev->device_id, rc));
			rc = TMF_RESP_FUNC_FAILED;
		}
	} else {
		rc = sas_phy_reset(phy, 1);
		msleep(2000);
	}
	PM8001_EH_DBG(pm8001_ha, pm8001_printk(" for device[%x]:rc=%d\n",
		pm8001_dev->device_id, rc));
 out:
	sas_put_local_phy(phy);
	return rc;
}