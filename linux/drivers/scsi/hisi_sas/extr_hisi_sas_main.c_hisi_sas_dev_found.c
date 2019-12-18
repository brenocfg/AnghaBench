#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct hisi_sas_device {scalar_t__ device_id; scalar_t__ dev_type; int /*<<< orphan*/  dev_status; } ;
struct hisi_hba {TYPE_1__* hw; struct device* dev; } ;
struct ex_phy {int /*<<< orphan*/  attached_sas_addr; } ;
struct TYPE_4__ {int num_phys; struct ex_phy* ex_phy; } ;
struct domain_device {int /*<<< orphan*/  sas_addr; TYPE_2__ ex_dev; int /*<<< orphan*/  dev_type; struct hisi_sas_device* lldd_dev; struct domain_device* parent; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* setup_itct ) (struct hisi_hba*,struct hisi_sas_device*) ;struct hisi_sas_device* (* alloc_dev ) (struct domain_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HISI_SAS_DEV_NORMAL ; 
 int /*<<< orphan*/  HISI_SAS_MAX_DEVICES ; 
 scalar_t__ SAS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ dev_is_expander (int /*<<< orphan*/ ) ; 
 struct hisi_hba* dev_to_hisi_hba (struct domain_device*) ; 
 struct hisi_sas_device* hisi_sas_alloc_dev (struct domain_device*) ; 
 int /*<<< orphan*/  hisi_sas_dev_gone (struct domain_device*) ; 
 int hisi_sas_init_device (struct domain_device*) ; 
 struct hisi_sas_device* stub1 (struct domain_device*) ; 
 int /*<<< orphan*/  stub2 (struct hisi_hba*,struct hisi_sas_device*) ; 

__attribute__((used)) static int hisi_sas_dev_found(struct domain_device *device)
{
	struct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	struct domain_device *parent_dev = device->parent;
	struct hisi_sas_device *sas_dev;
	struct device *dev = hisi_hba->dev;
	int rc;

	if (hisi_hba->hw->alloc_dev)
		sas_dev = hisi_hba->hw->alloc_dev(device);
	else
		sas_dev = hisi_sas_alloc_dev(device);
	if (!sas_dev) {
		dev_err(dev, "fail alloc dev: max support %d devices\n",
			HISI_SAS_MAX_DEVICES);
		return -EINVAL;
	}

	device->lldd_dev = sas_dev;
	hisi_hba->hw->setup_itct(hisi_hba, sas_dev);

	if (parent_dev && dev_is_expander(parent_dev->dev_type)) {
		int phy_no;
		u8 phy_num = parent_dev->ex_dev.num_phys;
		struct ex_phy *phy;

		for (phy_no = 0; phy_no < phy_num; phy_no++) {
			phy = &parent_dev->ex_dev.ex_phy[phy_no];
			if (SAS_ADDR(phy->attached_sas_addr) ==
				SAS_ADDR(device->sas_addr))
				break;
		}

		if (phy_no == phy_num) {
			dev_info(dev, "dev found: no attached "
				 "dev:%016llx at ex:%016llx\n",
				 SAS_ADDR(device->sas_addr),
				 SAS_ADDR(parent_dev->sas_addr));
			rc = -EINVAL;
			goto err_out;
		}
	}

	dev_info(dev, "dev[%d:%x] found\n",
		sas_dev->device_id, sas_dev->dev_type);

	rc = hisi_sas_init_device(device);
	if (rc)
		goto err_out;
	sas_dev->dev_status = HISI_SAS_DEV_NORMAL;
	return 0;

err_out:
	hisi_sas_dev_gone(device);
	return rc;
}