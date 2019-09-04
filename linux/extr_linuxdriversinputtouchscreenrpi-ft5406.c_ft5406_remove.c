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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct ft5406 {scalar_t__ input_dev; scalar_t__ ts_base; scalar_t__ bus_addr; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ft5406_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ft5406 *ts = (struct ft5406 *) platform_get_drvdata(pdev);

	dev_info(dev, "Removing rpi-ft5406\n");

	kthread_stop(ts->thread);

	if (ts->bus_addr)
		dma_free_coherent(dev, PAGE_SIZE, ts->ts_base, ts->bus_addr);
	else if (ts->ts_base)
		iounmap(ts->ts_base);
	if (ts->input_dev)
		input_unregister_device(ts->input_dev);

	return 0;
}