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
struct regulator_dev {scalar_t__ ref_cnt; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * mutex_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_nesting_mutex ; 
 int /*<<< orphan*/  ww_mutex_unlock (int /*<<< orphan*/ *) ; 

void regulator_unlock(struct regulator_dev *rdev)
{
	mutex_lock(&regulator_nesting_mutex);

	if (--rdev->ref_cnt == 0) {
		rdev->mutex_owner = NULL;
		ww_mutex_unlock(&rdev->mutex);
	}

	WARN_ON_ONCE(rdev->ref_cnt < 0);

	mutex_unlock(&regulator_nesting_mutex);
}