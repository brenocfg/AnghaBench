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
struct fxas21002c_data {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int  fxas21002c_pm_get(struct fxas21002c_data *data)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;

	ret = pm_runtime_get_sync(dev);
	if (ret < 0)
		pm_runtime_put_noidle(dev);

	return ret;
}