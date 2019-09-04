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
struct TYPE_2__ {int base; } ;
struct scoop_dev {int /*<<< orphan*/  base; TYPE_1__ gpio; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scoop_dev*) ; 
 struct scoop_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scoop_remove(struct platform_device *pdev)
{
	struct scoop_dev *sdev = platform_get_drvdata(pdev);

	if (!sdev)
		return -EINVAL;

	if (sdev->gpio.base != -1)
		gpiochip_remove(&sdev->gpio);

	platform_set_drvdata(pdev, NULL);
	iounmap(sdev->base);
	kfree(sdev);

	return 0;
}