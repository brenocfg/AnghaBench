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
typedef  int /*<<< orphan*/  u8 ;
struct hisi_sas_tmf_task {int /*<<< orphan*/  tmf; } ;
struct hisi_hba {struct device* dev; } ;
struct domain_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HISI_SAS_INT_ABT_DEV ; 
 int /*<<< orphan*/  TMF_ABORT_TASK_SET ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int TMF_RESP_FUNC_FAILED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct hisi_hba* dev_to_hisi_hba (struct domain_device*) ; 
 int hisi_sas_debug_issue_ssp_tmf (struct domain_device*,int /*<<< orphan*/ *,struct hisi_sas_tmf_task*) ; 
 int /*<<< orphan*/  hisi_sas_dereg_device (struct hisi_hba*,struct domain_device*) ; 
 int hisi_sas_internal_task_abort (struct hisi_hba*,struct domain_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_release_task (struct hisi_hba*,struct domain_device*) ; 

__attribute__((used)) static int hisi_sas_abort_task_set(struct domain_device *device, u8 *lun)
{
	struct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	struct device *dev = hisi_hba->dev;
	struct hisi_sas_tmf_task tmf_task;
	int rc;

	rc = hisi_sas_internal_task_abort(hisi_hba, device,
					  HISI_SAS_INT_ABT_DEV, 0);
	if (rc < 0) {
		dev_err(dev, "abort task set: internal abort rc=%d\n", rc);
		return TMF_RESP_FUNC_FAILED;
	}
	hisi_sas_dereg_device(hisi_hba, device);

	tmf_task.tmf = TMF_ABORT_TASK_SET;
	rc = hisi_sas_debug_issue_ssp_tmf(device, lun, &tmf_task);

	if (rc == TMF_RESP_FUNC_COMPLETE)
		hisi_sas_release_task(hisi_hba, device);

	return rc;
}