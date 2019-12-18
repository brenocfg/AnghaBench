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
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; } ;
struct tc_dev {TYPE_1__ resource; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct fza_private {int /*<<< orphan*/  mmio; int /*<<< orphan*/  reset_timer; } ;
struct device {int dummy; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  fza_do_shutdown (struct fza_private*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct fza_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 struct tc_dev* to_tc_dev (struct device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int fza_remove(struct device *bdev)
{
	struct net_device *dev = dev_get_drvdata(bdev);
	struct fza_private *fp = netdev_priv(dev);
	struct tc_dev *tdev = to_tc_dev(bdev);
	resource_size_t start, len;

	put_device(bdev);

	unregister_netdev(dev);

	del_timer_sync(&fp->reset_timer);
	fza_do_shutdown(fp);
	free_irq(dev->irq, dev);

	iounmap(fp->mmio);

	start = tdev->resource.start;
	len = tdev->resource.end - start + 1;
	release_mem_region(start, len);

	free_netdev(dev);

	return 0;
}