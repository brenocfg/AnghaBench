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
struct highlander_i2c_dev {int /*<<< orphan*/  base; scalar_t__ irq; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct highlander_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct highlander_i2c_dev*) ; 
 struct highlander_i2c_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int highlander_i2c_remove(struct platform_device *pdev)
{
	struct highlander_i2c_dev *dev = platform_get_drvdata(pdev);

	i2c_del_adapter(&dev->adapter);

	if (dev->irq)
		free_irq(dev->irq, dev);

	iounmap(dev->base);
	kfree(dev);

	return 0;
}