#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {struct platform_device* driver_data; } ;

/* Variables and functions */
 TYPE_1__ brcm_avs_driver ; 
 int brcm_avs_prepare_init (struct platform_device*) ; 
 int cpufreq_register_driver (TYPE_1__*) ; 

__attribute__((used)) static int brcm_avs_cpufreq_probe(struct platform_device *pdev)
{
	int ret;

	ret = brcm_avs_prepare_init(pdev);
	if (ret)
		return ret;

	brcm_avs_driver.driver_data = pdev;

	return cpufreq_register_driver(&brcm_avs_driver);
}