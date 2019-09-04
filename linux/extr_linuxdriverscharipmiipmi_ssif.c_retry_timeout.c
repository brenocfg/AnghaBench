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
struct timer_list {int dummy; } ;
struct ssif_info {int waiting_alert; scalar_t__ stopping; } ;

/* Variables and functions */
 struct ssif_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 unsigned long* ipmi_ssif_lock_cond (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  ipmi_ssif_unlock_cond (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  retry_timer ; 
 struct ssif_info* ssif_info ; 
 int /*<<< orphan*/  start_get (struct ssif_info*) ; 

__attribute__((used)) static void retry_timeout(struct timer_list *t)
{
	struct ssif_info *ssif_info = from_timer(ssif_info, t, retry_timer);
	unsigned long oflags, *flags;
	bool waiting;

	if (ssif_info->stopping)
		return;

	flags = ipmi_ssif_lock_cond(ssif_info, &oflags);
	waiting = ssif_info->waiting_alert;
	ssif_info->waiting_alert = false;
	ipmi_ssif_unlock_cond(ssif_info, flags);

	if (waiting)
		start_get(ssif_info);
}