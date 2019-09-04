#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct devfreq_event_dev {int enable_count; int /*<<< orphan*/  lock; TYPE_2__* desc; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* disable ) (struct devfreq_event_dev*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct devfreq_event_dev*) ; 

int devfreq_event_disable_edev(struct devfreq_event_dev *edev)
{
	int ret = 0;

	if (!edev || !edev->desc)
		return -EINVAL;

	mutex_lock(&edev->lock);
	if (edev->enable_count <= 0) {
		dev_warn(&edev->dev, "unbalanced enable_count\n");
		ret = -EIO;
		goto err;
	}

	if (edev->desc->ops && edev->desc->ops->disable
			&& edev->enable_count == 1) {
		ret = edev->desc->ops->disable(edev);
		if (ret < 0)
			goto err;
	}
	edev->enable_count--;
err:
	mutex_unlock(&edev->lock);

	return ret;
}