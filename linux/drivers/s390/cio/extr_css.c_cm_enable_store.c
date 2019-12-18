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
struct channel_subsystem {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cm_enabled; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int chsc_secm (struct channel_subsystem*,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct channel_subsystem* to_css (struct device*) ; 

__attribute__((used)) static ssize_t cm_enable_store(struct device *dev, struct device_attribute *a,
			       const char *buf, size_t count)
{
	struct channel_subsystem *css = to_css(dev);
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 16, &val);
	if (ret)
		return ret;
	mutex_lock(&css->mutex);
	switch (val) {
	case 0:
		ret = css->cm_enabled ? chsc_secm(css, 0) : 0;
		break;
	case 1:
		ret = css->cm_enabled ? 0 : chsc_secm(css, 1);
		break;
	default:
		ret = -EINVAL;
	}
	mutex_unlock(&css->mutex);
	return ret < 0 ? ret : count;
}