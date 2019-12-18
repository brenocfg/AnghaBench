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
struct regulator_dev {int dummy; } ;
struct lochnagar {int /*<<< orphan*/  analogue_config_lock; } ;

/* Variables and functions */
 int lochnagar_update_config (struct lochnagar*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct lochnagar* rdev_get_drvdata (struct regulator_dev*) ; 
 int regulator_disable_regmap (struct regulator_dev*) ; 

__attribute__((used)) static int lochnagar_micbias_disable(struct regulator_dev *rdev)
{
	struct lochnagar *lochnagar = rdev_get_drvdata(rdev);
	int ret;

	mutex_lock(&lochnagar->analogue_config_lock);

	ret = regulator_disable_regmap(rdev);
	if (ret < 0)
		goto err;

	ret = lochnagar_update_config(lochnagar);

err:
	mutex_unlock(&lochnagar->analogue_config_lock);

	return ret;
}