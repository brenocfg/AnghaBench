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
struct inode {int dummy; } ;
struct file {struct platform_device* private_data; } ;
struct dfl_feature_platform_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __port_reset (struct platform_device*) ; 
 int /*<<< orphan*/  afu_dma_region_destroy (struct dfl_feature_platform_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct dfl_feature_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfl_feature_dev_use_end (struct dfl_feature_platform_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afu_release(struct inode *inode, struct file *filp)
{
	struct platform_device *pdev = filp->private_data;
	struct dfl_feature_platform_data *pdata;

	dev_dbg(&pdev->dev, "Device File Release\n");

	pdata = dev_get_platdata(&pdev->dev);

	mutex_lock(&pdata->lock);
	__port_reset(pdev);
	afu_dma_region_destroy(pdata);
	mutex_unlock(&pdata->lock);

	dfl_feature_dev_use_end(pdata);

	return 0;
}