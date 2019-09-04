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
struct ipmi_user {struct ipmi_smi* intf; } ;
struct ipmi_smi {int /*<<< orphan*/  event_waiters; int /*<<< orphan*/  cmd_rcvrs_mutex; } ;
struct cmd_rcvr {unsigned int chans; struct cmd_rcvr* next; int /*<<< orphan*/  link; struct ipmi_user* user; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int IPMI_NUM_CHANNELS ; 
 struct ipmi_user* acquire_ipmi_user (struct ipmi_user*,int*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct cmd_rcvr* find_cmd_rcvr (struct ipmi_smi*,unsigned char,unsigned char,int) ; 
 int /*<<< orphan*/  kfree (struct cmd_rcvr*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_ipmi_user (struct ipmi_user*,int) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

int ipmi_unregister_for_cmd(struct ipmi_user *user,
			    unsigned char netfn,
			    unsigned char cmd,
			    unsigned int  chans)
{
	struct ipmi_smi *intf = user->intf;
	struct cmd_rcvr *rcvr;
	struct cmd_rcvr *rcvrs = NULL;
	int i, rv = -ENOENT, index;

	user = acquire_ipmi_user(user, &index);
	if (!user)
		return -ENODEV;

	mutex_lock(&intf->cmd_rcvrs_mutex);
	for (i = 0; i < IPMI_NUM_CHANNELS; i++) {
		if (((1 << i) & chans) == 0)
			continue;
		rcvr = find_cmd_rcvr(intf, netfn, cmd, i);
		if (rcvr == NULL)
			continue;
		if (rcvr->user == user) {
			rv = 0;
			rcvr->chans &= ~chans;
			if (rcvr->chans == 0) {
				list_del_rcu(&rcvr->link);
				rcvr->next = rcvrs;
				rcvrs = rcvr;
			}
		}
	}
	mutex_unlock(&intf->cmd_rcvrs_mutex);
	synchronize_rcu();
	release_ipmi_user(user, index);
	while (rcvrs) {
		atomic_dec(&intf->event_waiters);
		rcvr = rcvrs;
		rcvrs = rcvr->next;
		kfree(rcvr);
	}

	return rv;
}