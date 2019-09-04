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
struct da9052_hwmon {int /*<<< orphan*/  tsidone; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int da9052_get_tsi_result (struct da9052_hwmon*,int) ; 
 int da9052_request_tsi_read (struct da9052_hwmon*,int) ; 
 struct da9052_hwmon* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t __da9052_read_tsi(struct device *dev, int channel)
{
	struct da9052_hwmon *hwmon = dev_get_drvdata(dev);
	int ret;

	reinit_completion(&hwmon->tsidone);

	ret = da9052_request_tsi_read(hwmon, channel);
	if (ret < 0)
		return ret;

	/* Wait for an conversion done interrupt */
	if (!wait_for_completion_timeout(&hwmon->tsidone,
					 msecs_to_jiffies(500)))
		return -ETIMEDOUT;

	return da9052_get_tsi_result(hwmon, channel);
}