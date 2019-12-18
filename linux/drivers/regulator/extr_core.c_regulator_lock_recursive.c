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
struct ww_acquire_ctx {int dummy; } ;
struct TYPE_3__ {int n_coupled; struct regulator_dev** coupled_rdevs; } ;
struct regulator_dev {TYPE_2__* supply; TYPE_1__ coupling_desc; } ;
struct TYPE_4__ {struct regulator_dev* rdev; } ;

/* Variables and functions */
 int EALREADY ; 
 int EDEADLK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int regulator_lock_nested (struct regulator_dev*,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  regulator_supply_is_couple (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_unlock_recursive (struct regulator_dev*,int) ; 

__attribute__((used)) static int regulator_lock_recursive(struct regulator_dev *rdev,
				    struct regulator_dev **new_contended_rdev,
				    struct regulator_dev **old_contended_rdev,
				    struct ww_acquire_ctx *ww_ctx)
{
	struct regulator_dev *c_rdev;
	int i, err;

	for (i = 0; i < rdev->coupling_desc.n_coupled; i++) {
		c_rdev = rdev->coupling_desc.coupled_rdevs[i];

		if (!c_rdev)
			continue;

		if (c_rdev != *old_contended_rdev) {
			err = regulator_lock_nested(c_rdev, ww_ctx);
			if (err) {
				if (err == -EDEADLK) {
					*new_contended_rdev = c_rdev;
					goto err_unlock;
				}

				/* shouldn't happen */
				WARN_ON_ONCE(err != -EALREADY);
			}
		} else {
			*old_contended_rdev = NULL;
		}

		if (c_rdev->supply && !regulator_supply_is_couple(c_rdev)) {
			err = regulator_lock_recursive(c_rdev->supply->rdev,
						       new_contended_rdev,
						       old_contended_rdev,
						       ww_ctx);
			if (err) {
				regulator_unlock(c_rdev);
				goto err_unlock;
			}
		}
	}

	return 0;

err_unlock:
	regulator_unlock_recursive(rdev, i);

	return err;
}