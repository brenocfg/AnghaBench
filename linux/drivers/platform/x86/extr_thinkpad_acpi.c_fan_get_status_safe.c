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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int fan_get_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fan_mutex ; 
 int /*<<< orphan*/  fan_update_desired_level (int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fan_get_status_safe(u8 *status)
{
	int rc;
	u8 s;

	if (mutex_lock_killable(&fan_mutex))
		return -ERESTARTSYS;
	rc = fan_get_status(&s);
	if (!rc)
		fan_update_desired_level(s);
	mutex_unlock(&fan_mutex);

	if (rc)
		return rc;
	if (status)
		*status = s;

	return 0;
}