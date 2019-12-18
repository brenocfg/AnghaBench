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
struct hisi_hba {struct device* dev; } ;
struct domain_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HISI_SAS_INT_ABT_DEV ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int TMF_RESP_FUNC_FAILED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 scalar_t__ dev_is_sata (struct domain_device*) ; 
 struct hisi_hba* dev_to_hisi_hba (struct domain_device*) ; 
 int hisi_sas_debug_I_T_nexus_reset (struct domain_device*) ; 
 int /*<<< orphan*/  hisi_sas_dereg_device (struct hisi_hba*,struct domain_device*) ; 
 int hisi_sas_internal_task_abort (struct hisi_hba*,struct domain_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_release_task (struct hisi_hba*,struct domain_device*) ; 
 int hisi_sas_softreset_ata_disk (struct domain_device*) ; 

__attribute__((used)) static int hisi_sas_I_T_nexus_reset(struct domain_device *device)
{
	struct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	struct device *dev = hisi_hba->dev;
	int rc;

	rc = hisi_sas_internal_task_abort(hisi_hba, device,
					  HISI_SAS_INT_ABT_DEV, 0);
	if (rc < 0) {
		dev_err(dev, "I_T nexus reset: internal abort (%d)\n", rc);
		return TMF_RESP_FUNC_FAILED;
	}
	hisi_sas_dereg_device(hisi_hba, device);

	if (dev_is_sata(device)) {
		rc = hisi_sas_softreset_ata_disk(device);
		if (rc == TMF_RESP_FUNC_FAILED)
			return TMF_RESP_FUNC_FAILED;
	}

	rc = hisi_sas_debug_I_T_nexus_reset(device);

	if ((rc == TMF_RESP_FUNC_COMPLETE) || (rc == -ENODEV))
		hisi_sas_release_task(hisi_hba, device);

	return rc;
}