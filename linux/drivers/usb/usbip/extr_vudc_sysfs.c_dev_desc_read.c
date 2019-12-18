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
struct vudc {int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_cached; int /*<<< orphan*/  dev_desc; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ dev_get_drvdata (struct device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t dev_desc_read(struct file *file, struct kobject *kobj,
			     struct bin_attribute *attr, char *out,
			     loff_t off, size_t count)
{
	struct device *dev = kobj_to_dev(kobj);
	struct vudc *udc = (struct vudc *)dev_get_drvdata(dev);
	char *desc_ptr = (char *) &udc->dev_desc;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&udc->lock, flags);
	if (!udc->desc_cached) {
		ret = -ENODEV;
		goto unlock;
	}

	memcpy(out, desc_ptr + off, count);
	ret = count;
unlock:
	spin_unlock_irqrestore(&udc->lock, flags);
	return ret;
}