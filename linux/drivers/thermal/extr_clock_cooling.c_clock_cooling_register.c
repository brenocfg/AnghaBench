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
struct thermal_cooling_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct clock_cooling_device {int id; TYPE_1__ clk_rate_change_nb; struct thermal_cooling_device* clk; int /*<<< orphan*/  clock_val; scalar_t__ clock_state; int /*<<< orphan*/  freq_table; struct thermal_cooling_device* cdev; struct device* dev; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  dev_name ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct thermal_cooling_device* ERR_CAST (struct thermal_cooling_device*) ; 
 struct thermal_cooling_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct thermal_cooling_device*) ; 
 int THERMAL_NAME_LENGTH ; 
 int /*<<< orphan*/  clk_notifier_register (struct thermal_cooling_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  clock_cooling_clock_notifier ; 
 int /*<<< orphan*/  clock_cooling_get_frequency (struct clock_cooling_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_cooling_ops ; 
 int /*<<< orphan*/  clock_ida ; 
 int dev_pm_opp_init_cpufreq_table (struct device*,int /*<<< orphan*/ *) ; 
 struct thermal_cooling_device* devm_clk_get (struct device*,char const*) ; 
 struct clock_cooling_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 struct thermal_cooling_device* thermal_cooling_device_register (char*,struct clock_cooling_device*,int /*<<< orphan*/ *) ; 

struct thermal_cooling_device *
clock_cooling_register(struct device *dev, const char *clock_name)
{
	struct thermal_cooling_device *cdev;
	struct clock_cooling_device *ccdev = NULL;
	char dev_name[THERMAL_NAME_LENGTH];
	int ret = 0;

	ccdev = devm_kzalloc(dev, sizeof(*ccdev), GFP_KERNEL);
	if (!ccdev)
		return ERR_PTR(-ENOMEM);

	mutex_init(&ccdev->lock);
	ccdev->dev = dev;
	ccdev->clk = devm_clk_get(dev, clock_name);
	if (IS_ERR(ccdev->clk))
		return ERR_CAST(ccdev->clk);

	ret = ida_simple_get(&clock_ida, 0, 0, GFP_KERNEL);
	if (ret < 0)
		return ERR_PTR(ret);
	ccdev->id = ret;

	snprintf(dev_name, sizeof(dev_name), "thermal-clock-%d", ccdev->id);

	cdev = thermal_cooling_device_register(dev_name, ccdev,
					       &clock_cooling_ops);
	if (IS_ERR(cdev)) {
		ida_simple_remove(&clock_ida, ccdev->id);
		return ERR_PTR(-EINVAL);
	}
	ccdev->cdev = cdev;
	ccdev->clk_rate_change_nb.notifier_call = clock_cooling_clock_notifier;

	/* Assuming someone has already filled the opp table for this device */
	ret = dev_pm_opp_init_cpufreq_table(dev, &ccdev->freq_table);
	if (ret) {
		ida_simple_remove(&clock_ida, ccdev->id);
		return ERR_PTR(ret);
	}
	ccdev->clock_state = 0;
	ccdev->clock_val = clock_cooling_get_frequency(ccdev, 0);

	clk_notifier_register(ccdev->clk, &ccdev->clk_rate_change_nb);

	return cdev;
}