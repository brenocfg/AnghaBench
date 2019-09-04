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
struct fsi_master_gpio {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_external_mode ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsi_master_unregister (int /*<<< orphan*/ *) ; 
 struct fsi_master_gpio* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int fsi_master_gpio_remove(struct platform_device *pdev)
{
	struct fsi_master_gpio *master = platform_get_drvdata(pdev);

	device_remove_file(&pdev->dev, &dev_attr_external_mode);

	fsi_master_unregister(&master->master);

	return 0;
}