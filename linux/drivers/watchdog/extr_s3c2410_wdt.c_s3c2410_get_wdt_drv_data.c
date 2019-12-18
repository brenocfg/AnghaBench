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
struct s3c2410_wdt_variant {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 struct s3c2410_wdt_variant* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 TYPE_1__* platform_get_device_id (struct platform_device*) ; 

__attribute__((used)) static inline const struct s3c2410_wdt_variant *
s3c2410_get_wdt_drv_data(struct platform_device *pdev)
{
	const struct s3c2410_wdt_variant *variant;

	variant = of_device_get_match_data(&pdev->dev);
	if (!variant) {
		/* Device matched by platform_device_id */
		variant = (struct s3c2410_wdt_variant *)
			   platform_get_device_id(pdev)->driver_data;
	}

	return variant;
}