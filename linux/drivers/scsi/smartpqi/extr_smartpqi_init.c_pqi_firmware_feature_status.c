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
struct pqi_firmware_feature {int /*<<< orphan*/  feature_name; scalar_t__ enabled; int /*<<< orphan*/  supported; } ;
struct pqi_ctrl_info {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqi_firmware_feature_status(struct pqi_ctrl_info *ctrl_info,
	struct pqi_firmware_feature *firmware_feature)
{
	if (!firmware_feature->supported) {
		dev_info(&ctrl_info->pci_dev->dev, "%s not supported by controller\n",
			firmware_feature->feature_name);
		return;
	}

	if (firmware_feature->enabled) {
		dev_info(&ctrl_info->pci_dev->dev,
			"%s enabled\n", firmware_feature->feature_name);
		return;
	}

	dev_err(&ctrl_info->pci_dev->dev, "failed to enable %s\n",
		firmware_feature->feature_name);
}