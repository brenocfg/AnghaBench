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
struct nfp_pf {int /*<<< orphan*/  hwmon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HWMON ; 
 int /*<<< orphan*/  IS_REACHABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 

void nfp_hwmon_unregister(struct nfp_pf *pf)
{
	if (!IS_REACHABLE(CONFIG_HWMON) || !pf->hwmon_dev)
		return;

	hwmon_device_unregister(pf->hwmon_dev);
}