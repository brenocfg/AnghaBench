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
struct msc {int /*<<< orphan*/  user_count; int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  iter_list; } ;
struct intel_th_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_unless_negative (int /*<<< orphan*/ *) ; 
 struct msc* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int msc_configure (struct msc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_th_msc_activate(struct intel_th_device *thdev)
{
	struct msc *msc = dev_get_drvdata(&thdev->dev);
	int ret = -EBUSY;

	if (!atomic_inc_unless_negative(&msc->user_count))
		return -ENODEV;

	mutex_lock(&msc->buf_mutex);

	/* if there are readers, refuse */
	if (list_empty(&msc->iter_list))
		ret = msc_configure(msc);

	mutex_unlock(&msc->buf_mutex);

	if (ret)
		atomic_dec(&msc->user_count);

	return ret;
}