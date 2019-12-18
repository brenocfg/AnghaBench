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
struct lm8323_chip {int kp_enabled; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct lm8323_chip* dev_get_drvdata (struct device*) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t lm8323_set_disable(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct lm8323_chip *lm = dev_get_drvdata(dev);
	int ret;
	unsigned int i;

	ret = kstrtouint(buf, 10, &i);
	if (ret)
		return ret;

	mutex_lock(&lm->lock);
	lm->kp_enabled = !i;
	mutex_unlock(&lm->lock);

	return count;
}