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

/* Variables and functions */
 scalar_t__ CHP_INFO_UPDATE_INTERVAL ; 
 int /*<<< orphan*/  chp_info ; 
 scalar_t__ chp_info_expires ; 
 int /*<<< orphan*/  info_lock ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sclp_chp_read_info (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int info_update(void)
{
	int rc;

	mutex_lock(&info_lock);
	rc = 0;
	if (time_after(jiffies, chp_info_expires)) {
		/* Data is too old, update. */
		rc = sclp_chp_read_info(&chp_info);
		chp_info_expires = jiffies + CHP_INFO_UPDATE_INTERVAL ;
	}
	mutex_unlock(&info_lock);

	return rc;
}