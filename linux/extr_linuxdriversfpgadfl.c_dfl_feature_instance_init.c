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
struct platform_device {int dummy; } ;
struct dfl_feature_platform_data {int dummy; } ;
struct dfl_feature_driver {TYPE_1__* ops; } ;
struct dfl_feature {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* init ) (struct platform_device*,struct dfl_feature*) ;} ;

/* Variables and functions */
 int stub1 (struct platform_device*,struct dfl_feature*) ; 

__attribute__((used)) static int dfl_feature_instance_init(struct platform_device *pdev,
				     struct dfl_feature_platform_data *pdata,
				     struct dfl_feature *feature,
				     struct dfl_feature_driver *drv)
{
	int ret;

	ret = drv->ops->init(pdev, feature);
	if (ret)
		return ret;

	feature->ops = drv->ops;

	return ret;
}