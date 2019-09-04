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
struct inode {int dummy; } ;
struct file {struct apm_user* private_data; } ;
struct apm_user {scalar_t__ standbys_pending; scalar_t__ suspends_pending; struct apm_user* next; } ;

/* Variables and functions */
 scalar_t__ check_apm_user (struct apm_user*,char*) ; 
 int /*<<< orphan*/  kfree (struct apm_user*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  standby () ; 
 scalar_t__ standbys_pending ; 
 int /*<<< orphan*/  suspend (int) ; 
 scalar_t__ suspends_pending ; 
 struct apm_user* user_list ; 
 int /*<<< orphan*/  user_list_lock ; 

__attribute__((used)) static int do_release(struct inode *inode, struct file *filp)
{
	struct apm_user *as;

	as = filp->private_data;
	if (check_apm_user(as, "release"))
		return 0;
	filp->private_data = NULL;
	if (as->standbys_pending > 0) {
		standbys_pending -= as->standbys_pending;
		if (standbys_pending <= 0)
			standby();
	}
	if (as->suspends_pending > 0) {
		suspends_pending -= as->suspends_pending;
		if (suspends_pending <= 0)
			(void) suspend(1);
	}
	spin_lock(&user_list_lock);
	if (user_list == as)
		user_list = as->next;
	else {
		struct apm_user *as1;

		for (as1 = user_list;
		     (as1 != NULL) && (as1->next != as);
		     as1 = as1->next)
			;
		if (as1 == NULL)
			pr_err("filp not in user list\n");
		else
			as1->next = as->next;
	}
	spin_unlock(&user_list_lock);
	kfree(as);
	return 0;
}