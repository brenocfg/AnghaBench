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
struct ww_acquire_ctx {int dummy; } ;
struct regulator_dev {int /*<<< orphan*/  ref_cnt; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_list_mutex ; 
 int regulator_lock_recursive (struct regulator_dev*,struct regulator_dev**,struct regulator_dev**,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_ww_class ; 
 int /*<<< orphan*/  ww_acquire_done (struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  ww_acquire_init (struct ww_acquire_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ww_mutex_lock_slow (int /*<<< orphan*/ *,struct ww_acquire_ctx*) ; 

__attribute__((used)) static void regulator_lock_dependent(struct regulator_dev *rdev,
				     struct ww_acquire_ctx *ww_ctx)
{
	struct regulator_dev *new_contended_rdev = NULL;
	struct regulator_dev *old_contended_rdev = NULL;
	int err;

	mutex_lock(&regulator_list_mutex);

	ww_acquire_init(ww_ctx, &regulator_ww_class);

	do {
		if (new_contended_rdev) {
			ww_mutex_lock_slow(&new_contended_rdev->mutex, ww_ctx);
			old_contended_rdev = new_contended_rdev;
			old_contended_rdev->ref_cnt++;
		}

		err = regulator_lock_recursive(rdev,
					       &new_contended_rdev,
					       &old_contended_rdev,
					       ww_ctx);

		if (old_contended_rdev)
			regulator_unlock(old_contended_rdev);

	} while (err == -EDEADLK);

	ww_acquire_done(ww_ctx);

	mutex_unlock(&regulator_list_mutex);
}