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

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 struct platform_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int gcc_msm8960_remove(struct platform_device *pdev)
{
	struct platform_device *tsens = platform_get_drvdata(pdev);

	platform_device_unregister(tsens);

	return 0;
}