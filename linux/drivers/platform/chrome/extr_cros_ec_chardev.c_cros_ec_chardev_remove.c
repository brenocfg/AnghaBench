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
struct chardev_data {int /*<<< orphan*/  misc; } ;

/* Variables and functions */
 struct chardev_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_chardev_remove(struct platform_device *pdev)
{
	struct chardev_data *data = dev_get_drvdata(&pdev->dev);

	misc_deregister(&data->misc);

	return 0;
}