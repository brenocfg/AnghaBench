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
struct tle62x0_state {int gpio_state; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,unsigned long) ; 
 struct tle62x0_state* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tle62x0_write (struct tle62x0_state*) ; 
 int to_gpio_num (struct device_attribute*) ; 

__attribute__((used)) static ssize_t tle62x0_gpio_store(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t len)
{
	struct tle62x0_state *st = dev_get_drvdata(dev);
	int gpio_num = to_gpio_num(attr);
	unsigned long val;
	char *endp;

	val = simple_strtoul(buf, &endp, 0);
	if (buf == endp)
		return -EINVAL;

	dev_dbg(dev, "setting gpio %d to %ld\n", gpio_num, val);

	mutex_lock(&st->lock);

	if (val)
		st->gpio_state |= 1 << gpio_num;
	else
		st->gpio_state &= ~(1 << gpio_num);

	tle62x0_write(st);
	mutex_unlock(&st->lock);

	return len;
}