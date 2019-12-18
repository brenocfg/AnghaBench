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
struct hisi_sas_device {int /*<<< orphan*/ * sas_device; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  device_id; } ;
struct hisi_hba {int /*<<< orphan*/  sem; TYPE_1__* hw; int /*<<< orphan*/  flags; struct device* dev; } ;
struct domain_device {struct hisi_sas_device* lldd_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_device ) (struct hisi_sas_device*) ;int /*<<< orphan*/  (* clear_itct ) (struct hisi_hba*,struct hisi_sas_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HISI_SAS_INT_ABT_DEV ; 
 int /*<<< orphan*/  HISI_SAS_RESET_BIT ; 
 int /*<<< orphan*/  SAS_PHY_UNUSED ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hisi_hba* dev_to_hisi_hba (struct domain_device*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hisi_sas_dereg_device (struct hisi_hba*,struct domain_device*) ; 
 int /*<<< orphan*/  hisi_sas_internal_task_abort (struct hisi_hba*,struct domain_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hisi_hba*,struct hisi_sas_device*) ; 
 int /*<<< orphan*/  stub2 (struct hisi_sas_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hisi_sas_dev_gone(struct domain_device *device)
{
	struct hisi_sas_device *sas_dev = device->lldd_dev;
	struct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	struct device *dev = hisi_hba->dev;

	dev_info(dev, "dev[%d:%x] is gone\n",
		 sas_dev->device_id, sas_dev->dev_type);

	down(&hisi_hba->sem);
	if (!test_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags)) {
		hisi_sas_internal_task_abort(hisi_hba, device,
					     HISI_SAS_INT_ABT_DEV, 0);

		hisi_sas_dereg_device(hisi_hba, device);

		hisi_hba->hw->clear_itct(hisi_hba, sas_dev);
		device->lldd_dev = NULL;
	}

	if (hisi_hba->hw->free_device)
		hisi_hba->hw->free_device(sas_dev);
	sas_dev->dev_type = SAS_PHY_UNUSED;
	sas_dev->sas_device = NULL;
	up(&hisi_hba->sem);
}