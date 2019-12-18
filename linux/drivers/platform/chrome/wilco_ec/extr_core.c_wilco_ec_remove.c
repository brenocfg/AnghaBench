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
struct wilco_ec_device {scalar_t__ debugfs_pdev; scalar_t__ rtc_pdev; scalar_t__ telem_pdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cros_ec_lpc_mec_destroy () ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 
 struct wilco_ec_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  wilco_ec_remove_sysfs (struct wilco_ec_device*) ; 

__attribute__((used)) static int wilco_ec_remove(struct platform_device *pdev)
{
	struct wilco_ec_device *ec = platform_get_drvdata(pdev);

	wilco_ec_remove_sysfs(ec);
	platform_device_unregister(ec->telem_pdev);
	platform_device_unregister(ec->rtc_pdev);
	if (ec->debugfs_pdev)
		platform_device_unregister(ec->debugfs_pdev);

	/* Teardown cros_ec interface */
	cros_ec_lpc_mec_destroy();

	return 0;
}