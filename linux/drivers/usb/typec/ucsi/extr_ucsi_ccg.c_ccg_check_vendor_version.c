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
struct version_format {int /*<<< orphan*/  build; } ;
struct ucsi_ccg {scalar_t__ fw_build; struct device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  build; } ;
struct fw_config_table {TYPE_1__ app; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ccg_check_vendor_version(struct ucsi_ccg *uc,
				     struct version_format *app,
				     struct fw_config_table *fw_cfg)
{
	struct device *dev = uc->dev;

	/* Check if the fw build is for supported vendors */
	if (le16_to_cpu(app->build) != uc->fw_build) {
		dev_info(dev, "current fw is not from supported vendor\n");
		return false;
	}

	/* Check if the new fw build is for supported vendors */
	if (le16_to_cpu(fw_cfg->app.build) != uc->fw_build) {
		dev_info(dev, "new fw is not from supported vendor\n");
		return false;
	}
	return true;
}