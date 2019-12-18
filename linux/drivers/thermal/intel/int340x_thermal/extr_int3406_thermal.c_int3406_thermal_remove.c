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
struct platform_device {int dummy; } ;
struct int3406_thermal_data {int /*<<< orphan*/  br; int /*<<< orphan*/  cooling_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct int3406_thermal_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int int3406_thermal_remove(struct platform_device *pdev)
{
	struct int3406_thermal_data *d = platform_get_drvdata(pdev);

	thermal_cooling_device_unregister(d->cooling_dev);
	kfree(d->br);
	return 0;
}