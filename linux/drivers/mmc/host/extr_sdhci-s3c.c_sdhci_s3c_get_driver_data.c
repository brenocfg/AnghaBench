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
struct sdhci_s3c_drv_data {int dummy; } ;
struct TYPE_3__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_4__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* platform_get_device_id (struct platform_device*) ; 
 int /*<<< orphan*/  sdhci_s3c_dt_match ; 

__attribute__((used)) static inline struct sdhci_s3c_drv_data *sdhci_s3c_get_driver_data(
			struct platform_device *pdev)
{
#ifdef CONFIG_OF
	if (pdev->dev.of_node) {
		const struct of_device_id *match;
		match = of_match_node(sdhci_s3c_dt_match, pdev->dev.of_node);
		return (struct sdhci_s3c_drv_data *)match->data;
	}
#endif
	return (struct sdhci_s3c_drv_data *)
			platform_get_device_id(pdev)->driver_data;
}