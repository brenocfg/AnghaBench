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
struct mcast_group {scalar_t__ retries; int /*<<< orphan*/  work; int /*<<< orphan*/  leave_state; } ;
struct ib_sa_mcmember_rec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcast_work_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_leave (struct mcast_group*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void leave_handler(int status, struct ib_sa_mcmember_rec *rec,
			  void *context)
{
	struct mcast_group *group = context;

	if (status && group->retries > 0 &&
	    !send_leave(group, group->leave_state))
		group->retries--;
	else
		mcast_work_handler(&group->work);
}