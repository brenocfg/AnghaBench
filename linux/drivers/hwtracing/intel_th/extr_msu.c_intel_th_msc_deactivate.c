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
struct msc {int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  user_count; scalar_t__ enabled; } ;
struct intel_th_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct msc* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msc_disable (struct msc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_th_msc_deactivate(struct intel_th_device *thdev)
{
	struct msc *msc = dev_get_drvdata(&thdev->dev);

	mutex_lock(&msc->buf_mutex);
	if (msc->enabled) {
		msc_disable(msc);
		atomic_dec(&msc->user_count);
	}
	mutex_unlock(&msc->buf_mutex);
}