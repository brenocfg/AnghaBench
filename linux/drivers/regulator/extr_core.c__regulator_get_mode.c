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
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int _regulator_get_mode_unlocked (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_lock (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 

__attribute__((used)) static unsigned int _regulator_get_mode(struct regulator_dev *rdev)
{
	int ret;

	regulator_lock(rdev);
	ret = _regulator_get_mode_unlocked(rdev);
	regulator_unlock(rdev);

	return ret;
}