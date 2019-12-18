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
struct occ {int last_error; int /*<<< orphan*/  lock; scalar_t__ last_update; } ;

/* Variables and functions */
 scalar_t__ OCC_UPDATE_FREQUENCY ; 
 scalar_t__ jiffies ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int occ_poll (struct occ*) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

int occ_update_response(struct occ *occ)
{
	int rc = mutex_lock_interruptible(&occ->lock);

	if (rc)
		return rc;

	/* limit the maximum rate of polling the OCC */
	if (time_after(jiffies, occ->last_update + OCC_UPDATE_FREQUENCY)) {
		rc = occ_poll(occ);
		occ->last_update = jiffies;
	} else {
		rc = occ->last_error;
	}

	mutex_unlock(&occ->lock);
	return rc;
}