#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sas_ha_struct {struct hisi_hba* lldd_ha; } ;
struct hisi_sas_device {scalar_t__ dev_type; int /*<<< orphan*/  device_id; struct domain_device* sas_device; } ;
struct hisi_hba {struct hisi_sas_device* devices; int /*<<< orphan*/  wq; struct device* dev; } ;
struct domain_device {int /*<<< orphan*/  dev_type; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  done; int /*<<< orphan*/  completion; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  HISI_SAS_DECLARE_RST_WORK_ON_STACK (TYPE_1__) ; 
 int HISI_SAS_MAX_DEVICES ; 
 scalar_t__ SAS_PHY_UNUSED ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int TMF_RESP_FUNC_FAILED ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dev_is_expander (int /*<<< orphan*/ ) ; 
 int hisi_sas_debug_I_T_nexus_reset (struct domain_device*) ; 
 int /*<<< orphan*/  hisi_sas_release_tasks (struct hisi_hba*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ r ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_sas_clear_nexus_ha(struct sas_ha_struct *sas_ha)
{
	struct hisi_hba *hisi_hba = sas_ha->lldd_ha;
	struct device *dev = hisi_hba->dev;
	HISI_SAS_DECLARE_RST_WORK_ON_STACK(r);
	int rc, i;

	queue_work(hisi_hba->wq, &r.work);
	wait_for_completion(r.completion);
	if (!r.done)
		return TMF_RESP_FUNC_FAILED;

	for (i = 0; i < HISI_SAS_MAX_DEVICES; i++) {
		struct hisi_sas_device *sas_dev = &hisi_hba->devices[i];
		struct domain_device *device = sas_dev->sas_device;

		if ((sas_dev->dev_type == SAS_PHY_UNUSED) || !device ||
		    dev_is_expander(device->dev_type))
			continue;

		rc = hisi_sas_debug_I_T_nexus_reset(device);
		if (rc != TMF_RESP_FUNC_COMPLETE)
			dev_info(dev, "clear nexus ha: for device[%d] rc=%d\n",
				 sas_dev->device_id, rc);
	}

	hisi_sas_release_tasks(hisi_hba);

	return TMF_RESP_FUNC_COMPLETE;
}