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
struct img_i2c {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  img_i2c_runtime_suspend (int /*<<< orphan*/ *) ; 
 struct img_i2c* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int img_i2c_remove(struct platform_device *dev)
{
	struct img_i2c *i2c = platform_get_drvdata(dev);

	i2c_del_adapter(&i2c->adap);
	pm_runtime_disable(&dev->dev);
	if (!pm_runtime_status_suspended(&dev->dev))
		img_i2c_runtime_suspend(&dev->dev);

	return 0;
}