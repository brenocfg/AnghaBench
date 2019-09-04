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
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct apds990x_chip {int lux; int lux_calib; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lux_wait_fresh_res; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int APDS990X_LUX_OUTPUT_SCALE ; 
 int APDS_CALIB_SCALER ; 
 int APDS_RANGE ; 
 int /*<<< orphan*/  APDS_TIMEOUT ; 
 int /*<<< orphan*/  EIO ; 
 struct apds990x_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_suspended (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t apds990x_lux_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct apds990x_chip *chip = dev_get_drvdata(dev);
	ssize_t ret;
	u32 result;
	long timeout;

	if (pm_runtime_suspended(dev))
		return -EIO;

	timeout = wait_event_interruptible_timeout(chip->wait,
						!chip->lux_wait_fresh_res,
						msecs_to_jiffies(APDS_TIMEOUT));
	if (!timeout)
		return -EIO;

	mutex_lock(&chip->mutex);
	result = (chip->lux * chip->lux_calib) / APDS_CALIB_SCALER;
	if (result > (APDS_RANGE * APDS990X_LUX_OUTPUT_SCALE))
		result = APDS_RANGE * APDS990X_LUX_OUTPUT_SCALE;

	ret = sprintf(buf, "%d.%d\n",
		result / APDS990X_LUX_OUTPUT_SCALE,
		result % APDS990X_LUX_OUTPUT_SCALE);
	mutex_unlock(&chip->mutex);
	return ret;
}