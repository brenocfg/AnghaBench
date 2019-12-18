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
struct iwl_notification_wait {scalar_t__ aborted; scalar_t__ triggered; } ;
struct iwl_notif_wait_data {int /*<<< orphan*/  notif_waitq; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  iwl_remove_notification (struct iwl_notif_wait_data*,struct iwl_notification_wait*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

int iwl_wait_notification(struct iwl_notif_wait_data *notif_wait,
			  struct iwl_notification_wait *wait_entry,
			  unsigned long timeout)
{
	int ret;

	ret = wait_event_timeout(notif_wait->notif_waitq,
				 wait_entry->triggered || wait_entry->aborted,
				 timeout);

	iwl_remove_notification(notif_wait, wait_entry);

	if (wait_entry->aborted)
		return -EIO;

	/* return value is always >= 0 */
	if (ret <= 0)
		return -ETIMEDOUT;
	return 0;
}