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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puv3_rtc_mem ; 
 int /*<<< orphan*/  puv3_rtc_setaie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puv3_rtc_setpie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int puv3_rtc_remove(struct platform_device *dev)
{
	puv3_rtc_setpie(&dev->dev, 0);
	puv3_rtc_setaie(&dev->dev, 0);

	release_resource(puv3_rtc_mem);
	kfree(puv3_rtc_mem);

	return 0;
}