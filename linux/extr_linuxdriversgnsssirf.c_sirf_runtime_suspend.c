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
struct sirf_data {int /*<<< orphan*/  vcc; int /*<<< orphan*/  on_off; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sirf_data* dev_get_drvdata (struct device*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int sirf_set_active (struct sirf_data*,int) ; 

__attribute__((used)) static int sirf_runtime_suspend(struct device *dev)
{
	struct sirf_data *data = dev_get_drvdata(dev);

	if (!data->on_off)
		return regulator_disable(data->vcc);

	return sirf_set_active(data, false);
}