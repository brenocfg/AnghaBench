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
struct nfp_pf {int /*<<< orphan*/  hwmon_dev; TYPE_2__* pdev; int /*<<< orphan*/  cpp; TYPE_1__* nspi; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  sensor_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HWMON ; 
 int /*<<< orphan*/  IS_REACHABLE (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register_with_info (int /*<<< orphan*/ *,char*,struct nfp_pf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_chip_info ; 
 int /*<<< orphan*/  nfp_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*) ; 

int nfp_hwmon_register(struct nfp_pf *pf)
{
	if (!IS_REACHABLE(CONFIG_HWMON))
		return 0;

	if (!pf->nspi) {
		nfp_warn(pf->cpp, "not registering HWMON (no NSP info)\n");
		return 0;
	}
	if (!pf->nspi->sensor_mask) {
		nfp_info(pf->cpp,
			 "not registering HWMON (NSP doesn't report sensors)\n");
		return 0;
	}

	pf->hwmon_dev = hwmon_device_register_with_info(&pf->pdev->dev, "nfp",
							pf, &nfp_chip_info,
							NULL);
	return PTR_ERR_OR_ZERO(pf->hwmon_dev);
}