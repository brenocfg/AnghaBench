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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bh1770_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  lux_wait_result; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BH1770_TIMEOUT ; 
 int /*<<< orphan*/  EIO ; 
 int bh1770_lux_read_result (struct bh1770_chip*) ; 
 struct bh1770_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_suspended (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t bh1770_lux_result_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct bh1770_chip *chip =  dev_get_drvdata(dev);
	ssize_t ret;
	long timeout;

	if (pm_runtime_suspended(dev))
		return -EIO; /* Chip is not enabled at all */

	timeout = wait_event_interruptible_timeout(chip->wait,
					!chip->lux_wait_result,
					msecs_to_jiffies(BH1770_TIMEOUT));
	if (!timeout)
		return -EIO;

	mutex_lock(&chip->mutex);
	ret = sprintf(buf, "%d\n", bh1770_lux_read_result(chip));
	mutex_unlock(&chip->mutex);

	return ret;
}