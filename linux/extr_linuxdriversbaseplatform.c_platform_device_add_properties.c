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
struct property_entry {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int device_add_properties (int /*<<< orphan*/ *,struct property_entry const*) ; 

int platform_device_add_properties(struct platform_device *pdev,
				   const struct property_entry *properties)
{
	return device_add_properties(&pdev->dev, properties);
}