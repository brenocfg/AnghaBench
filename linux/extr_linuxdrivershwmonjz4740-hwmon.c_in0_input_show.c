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
struct platform_device {int dummy; } ;
struct completion {int dummy; } ;
struct jz4740_hwmon {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; TYPE_1__* cell; int /*<<< orphan*/  base; struct completion read_completion; struct platform_device* pdev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct platform_device*) ;int /*<<< orphan*/  (* enable ) (struct platform_device*) ;} ;

/* Variables and functions */
 long ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 struct jz4740_hwmon* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (struct completion*) ; 
 int sprintf (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  stub2 (struct platform_device*) ; 
 long wait_for_completion_interruptible_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t in0_input_show(struct device *dev,
			      struct device_attribute *dev_attr, char *buf)
{
	struct jz4740_hwmon *hwmon = dev_get_drvdata(dev);
	struct platform_device *pdev = hwmon->pdev;
	struct completion *completion = &hwmon->read_completion;
	long t;
	unsigned long val;
	int ret;

	mutex_lock(&hwmon->lock);

	reinit_completion(completion);

	enable_irq(hwmon->irq);
	hwmon->cell->enable(pdev);

	t = wait_for_completion_interruptible_timeout(completion, HZ);

	if (t > 0) {
		val = readw(hwmon->base) & 0xfff;
		val = (val * 3300) >> 12;
		ret = sprintf(buf, "%lu\n", val);
	} else {
		ret = t ? t : -ETIMEDOUT;
	}

	hwmon->cell->disable(pdev);
	disable_irq(hwmon->irq);

	mutex_unlock(&hwmon->lock);

	return ret;
}