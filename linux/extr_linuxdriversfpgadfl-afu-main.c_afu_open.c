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
struct dfl_feature_platform_data {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct dfl_feature_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int dfl_feature_dev_use_begin (struct dfl_feature_platform_data*) ; 
 struct platform_device* dfl_fpga_inode_to_feature_dev (struct inode*) ; 

__attribute__((used)) static int afu_open(struct inode *inode, struct file *filp)
{
	struct platform_device *fdev = dfl_fpga_inode_to_feature_dev(inode);
	struct dfl_feature_platform_data *pdata;
	int ret;

	pdata = dev_get_platdata(&fdev->dev);
	if (WARN_ON(!pdata))
		return -ENODEV;

	ret = dfl_feature_dev_use_begin(pdata);
	if (ret)
		return ret;

	dev_dbg(&fdev->dev, "Device File Open\n");
	filp->private_data = fdev;

	return 0;
}