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
struct dim2_hdm {int /*<<< orphan*/  (* disable_platform ) (struct platform_device*) ;int /*<<< orphan*/  netinfo_task; int /*<<< orphan*/  most_iface; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dim2_sysfs_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dim_lock ; 
 int /*<<< orphan*/  dim_shutdown () ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  most_deregister_interface (int /*<<< orphan*/ *) ; 
 struct dim2_hdm* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 

__attribute__((used)) static int dim2_remove(struct platform_device *pdev)
{
	struct dim2_hdm *dev = platform_get_drvdata(pdev);
	unsigned long flags;

	dim2_sysfs_destroy(&dev->dev);
	most_deregister_interface(&dev->most_iface);
	kthread_stop(dev->netinfo_task);

	spin_lock_irqsave(&dim_lock, flags);
	dim_shutdown();
	spin_unlock_irqrestore(&dim_lock, flags);

	if (dev->disable_platform)
		dev->disable_platform(pdev);

	return 0;
}