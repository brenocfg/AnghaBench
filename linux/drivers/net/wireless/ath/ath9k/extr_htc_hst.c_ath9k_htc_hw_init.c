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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct htc_target {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ ath9k_htc_probe_device (struct htc_target*,struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int ath9k_htc_hw_init(struct htc_target *target,
		      struct device *dev, u16 devid,
		      char *product, u32 drv_info)
{
	if (ath9k_htc_probe_device(target, dev, devid, product, drv_info)) {
		pr_err("Failed to initialize the device\n");
		return -ENODEV;
	}

	return 0;
}