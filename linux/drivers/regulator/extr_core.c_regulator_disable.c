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
struct regulator_dev {int dummy; } ;
struct regulator {struct regulator_dev* rdev; } ;

/* Variables and functions */
 int _regulator_disable (struct regulator*) ; 
 int /*<<< orphan*/  regulator_lock_dependent (struct regulator_dev*,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  regulator_unlock_dependent (struct regulator_dev*,struct ww_acquire_ctx*) ; 

int regulator_disable(struct regulator *regulator)
{
	struct regulator_dev *rdev = regulator->rdev;
	struct ww_acquire_ctx ww_ctx;
	int ret;

	regulator_lock_dependent(rdev, &ww_ctx);
	ret = _regulator_disable(regulator);
	regulator_unlock_dependent(rdev, &ww_ctx);

	return ret;
}