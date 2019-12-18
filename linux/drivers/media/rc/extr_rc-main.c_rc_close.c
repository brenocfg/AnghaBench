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
struct rc_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  (* close ) (struct rc_dev*) ;scalar_t__ registered; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rc_dev*) ; 

void rc_close(struct rc_dev *rdev)
{
	if (rdev) {
		mutex_lock(&rdev->lock);

		if (!--rdev->users && rdev->close && rdev->registered)
			rdev->close(rdev);

		mutex_unlock(&rdev->lock);
	}
}