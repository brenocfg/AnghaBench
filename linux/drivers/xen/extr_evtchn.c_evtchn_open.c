#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct per_user_data {int /*<<< orphan*/  restrict_domid; int /*<<< orphan*/  ring_prod_lock; int /*<<< orphan*/  ring_cons_mutex; int /*<<< orphan*/  bind_mutex; int /*<<< orphan*/  evtchn_wait; int /*<<< orphan*/ * name; } ;
struct inode {int dummy; } ;
struct file {struct per_user_data* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UNRESTRICTED_DOMID ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct per_user_data*) ; 
 struct per_user_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stream_open (struct inode*,struct file*) ; 

__attribute__((used)) static int evtchn_open(struct inode *inode, struct file *filp)
{
	struct per_user_data *u;

	u = kzalloc(sizeof(*u), GFP_KERNEL);
	if (u == NULL)
		return -ENOMEM;

	u->name = kasprintf(GFP_KERNEL, "evtchn:%s", current->comm);
	if (u->name == NULL) {
		kfree(u);
		return -ENOMEM;
	}

	init_waitqueue_head(&u->evtchn_wait);

	mutex_init(&u->bind_mutex);
	mutex_init(&u->ring_cons_mutex);
	spin_lock_init(&u->ring_prod_lock);

	u->restrict_domid = UNRESTRICTED_DOMID;

	filp->private_data = u;

	return stream_open(inode, filp);
}