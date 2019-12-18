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
typedef  union acpi_object {int dummy; } acpi_object ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  DSM_FUNC_ERR_HANDLE_MSI ; 
 int EINVAL ; 
 union acpi_object* acpi_evaluate_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ guid_parse (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_reg_v3_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int reset_hw_v3_hw (struct hisi_hba*) ; 

__attribute__((used)) static int hw_init_v3_hw(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	union acpi_object *obj;
	guid_t guid;
	int rc;

	rc = reset_hw_v3_hw(hisi_hba);
	if (rc) {
		dev_err(dev, "hisi_sas_reset_hw failed, rc=%d", rc);
		return rc;
	}

	msleep(100);
	init_reg_v3_hw(hisi_hba);

	if (guid_parse("D5918B4B-37AE-4E10-A99F-E5E8A6EF4C1F", &guid)) {
		dev_err(dev, "Parse GUID failed\n");
		return -EINVAL;
	}

	/* Switch over to MSI handling , from PCI AER default */
	obj = acpi_evaluate_dsm(ACPI_HANDLE(dev), &guid, 0,
				DSM_FUNC_ERR_HANDLE_MSI, NULL);
	if (!obj)
		dev_warn(dev, "Switch over to MSI handling failed\n");
	else
		ACPI_FREE(obj);

	return 0;
}