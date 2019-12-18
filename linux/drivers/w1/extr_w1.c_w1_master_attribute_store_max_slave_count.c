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
struct w1_master {int max_slave_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  flags; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  W1_WARN_MAX_COUNT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct w1_master* dev_to_w1_master (struct device*) ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t w1_master_attribute_store_max_slave_count(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int tmp;
	struct w1_master *md = dev_to_w1_master(dev);

	if (kstrtoint(buf, 0, &tmp) || tmp < 1)
		return -EINVAL;

	mutex_lock(&md->mutex);
	md->max_slave_count = tmp;
	/* allow each time the max_slave_count is updated */
	clear_bit(W1_WARN_MAX_COUNT, &md->flags);
	mutex_unlock(&md->mutex);

	return count;
}