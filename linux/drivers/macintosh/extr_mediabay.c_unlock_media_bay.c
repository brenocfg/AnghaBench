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
struct media_bay_info {int /*<<< orphan*/  lock; scalar_t__ user_lock; } ;
struct macio_dev {int dummy; } ;

/* Variables and functions */
 struct media_bay_info* macio_get_drvdata (struct macio_dev*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void unlock_media_bay(struct macio_dev *baydev)
{
	struct media_bay_info* bay;

	if (baydev == NULL)
		return;
	bay = macio_get_drvdata(baydev);
	if (bay == NULL)
		return;
	if (bay->user_lock) {
		bay->user_lock = 0;
		mutex_unlock(&bay->lock);
	}
}