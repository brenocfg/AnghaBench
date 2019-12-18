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
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int pm_runtime_put_autosuspend (struct device*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int  fxas21002c_pm_put(struct fxas21002c_data *data)
{
	struct device *dev = regmap_get_device(data->regmap);

	pm_runtime_mark_last_busy(dev);

	return pm_runtime_put_autosuspend(dev);
}