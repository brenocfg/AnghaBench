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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cyapa {int /*<<< orphan*/  state_sync_lock; TYPE_1__* ops; scalar_t__ operational; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* show_baseline ) (struct device*,struct device_attribute*,char*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  cyapa_disable_irq_for_cmd (struct cyapa*) ; 
 int /*<<< orphan*/  cyapa_enable_irq_for_cmd (struct cyapa*) ; 
 struct cyapa* dev_get_drvdata (struct device*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct device*,struct device_attribute*,char*) ; 

__attribute__((used)) static ssize_t cyapa_show_baseline(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct cyapa *cyapa = dev_get_drvdata(dev);
	ssize_t error;

	error = mutex_lock_interruptible(&cyapa->state_sync_lock);
	if (error)
		return error;

	if (cyapa->operational) {
		cyapa_enable_irq_for_cmd(cyapa);
		error = cyapa->ops->show_baseline(dev, attr, buf);
		cyapa_disable_irq_for_cmd(cyapa);
	} else {
		error = -EBUSY;  /* Still running in bootloader mode. */
	}

	mutex_unlock(&cyapa->state_sync_lock);
	return error;
}