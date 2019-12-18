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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int gpio_keys_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gpio_keys_shutdown(struct platform_device *pdev)
{
	int ret;

	ret = gpio_keys_suspend(&pdev->dev);
	if (ret)
		dev_err(&pdev->dev, "failed to shutdown\n");
}