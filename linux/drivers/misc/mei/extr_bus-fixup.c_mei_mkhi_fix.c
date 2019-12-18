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
struct mei_cl_device {int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ hbm_f_os_supported; scalar_t__ fw_f_fw_ver_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mei_cldev_disable (struct mei_cl_device*) ; 
 int mei_cldev_enable (struct mei_cl_device*) ; 
 int mei_fwver (struct mei_cl_device*) ; 
 int mei_osver (struct mei_cl_device*) ; 

__attribute__((used)) static void mei_mkhi_fix(struct mei_cl_device *cldev)
{
	int ret;

	/* No need to enable the client if nothing is needed from it */
	if (!cldev->bus->fw_f_fw_ver_supported &&
	    !cldev->bus->hbm_f_os_supported)
		return;

	ret = mei_cldev_enable(cldev);
	if (ret)
		return;

	if (cldev->bus->fw_f_fw_ver_supported) {
		ret = mei_fwver(cldev);
		if (ret < 0)
			dev_err(&cldev->dev, "FW version command failed %d\n",
				ret);
	}

	if (cldev->bus->hbm_f_os_supported) {
		ret = mei_osver(cldev);
		if (ret < 0)
			dev_err(&cldev->dev, "OS version command failed %d\n",
				ret);
	}
	mei_cldev_disable(cldev);
}