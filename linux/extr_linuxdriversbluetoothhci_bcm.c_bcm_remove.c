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
struct bcm_device {int /*<<< orphan*/  name; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_device_lock ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bcm_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int bcm_remove(struct platform_device *pdev)
{
	struct bcm_device *dev = platform_get_drvdata(pdev);

	mutex_lock(&bcm_device_lock);
	list_del(&dev->list);
	mutex_unlock(&bcm_device_lock);

	dev_info(&pdev->dev, "%s device unregistered.\n", dev->name);

	return 0;
}