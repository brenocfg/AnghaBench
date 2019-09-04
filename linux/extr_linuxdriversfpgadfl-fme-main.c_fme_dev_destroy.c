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
struct dfl_fme {int dummy; } ;
struct dfl_feature_platform_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct dfl_feature_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct dfl_fme* dfl_fpga_pdata_get_private (struct dfl_feature_platform_data*) ; 
 int /*<<< orphan*/  dfl_fpga_pdata_set_private (struct dfl_feature_platform_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fme_dev_destroy(struct platform_device *pdev)
{
	struct dfl_feature_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct dfl_fme *fme;

	mutex_lock(&pdata->lock);
	fme = dfl_fpga_pdata_get_private(pdata);
	dfl_fpga_pdata_set_private(pdata, NULL);
	mutex_unlock(&pdata->lock);
}