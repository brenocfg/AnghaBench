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
struct rc_dev {int (* open ) (struct rc_dev*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  users; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct rc_dev*) ; 

int rc_open(struct rc_dev *rdev)
{
	int rval = 0;

	if (!rdev)
		return -EINVAL;

	mutex_lock(&rdev->lock);

	if (!rdev->registered) {
		rval = -ENODEV;
	} else {
		if (!rdev->users++ && rdev->open)
			rval = rdev->open(rdev);

		if (rval)
			rdev->users--;
	}

	mutex_unlock(&rdev->lock);

	return rval;
}