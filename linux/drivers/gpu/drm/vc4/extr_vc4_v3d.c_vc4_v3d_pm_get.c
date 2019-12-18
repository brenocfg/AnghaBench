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
struct vc4_dev {int /*<<< orphan*/  power_lock; int /*<<< orphan*/  power_refcount; TYPE_2__* v3d; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 

int
vc4_v3d_pm_get(struct vc4_dev *vc4)
{
	mutex_lock(&vc4->power_lock);
	if (vc4->power_refcount++ == 0) {
		int ret = pm_runtime_get_sync(&vc4->v3d->pdev->dev);

		if (ret < 0) {
			vc4->power_refcount--;
			mutex_unlock(&vc4->power_lock);
			return ret;
		}
	}
	mutex_unlock(&vc4->power_lock);

	return 0;
}