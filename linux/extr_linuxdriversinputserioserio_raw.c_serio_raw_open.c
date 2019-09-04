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
struct serio_raw_client {int /*<<< orphan*/  node; struct serio_raw* serio_raw; } ;
struct serio_raw {int /*<<< orphan*/  serio; int /*<<< orphan*/  client_list; int /*<<< orphan*/  kref; scalar_t__ dead; } ;
struct inode {int dummy; } ;
struct file {struct serio_raw_client* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct serio_raw_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_continue_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_pause_rx (int /*<<< orphan*/ ) ; 
 struct serio_raw* serio_raw_locate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_raw_mutex ; 

__attribute__((used)) static int serio_raw_open(struct inode *inode, struct file *file)
{
	struct serio_raw *serio_raw;
	struct serio_raw_client *client;
	int retval;

	retval = mutex_lock_interruptible(&serio_raw_mutex);
	if (retval)
		return retval;

	serio_raw = serio_raw_locate(iminor(inode));
	if (!serio_raw) {
		retval = -ENODEV;
		goto out;
	}

	if (serio_raw->dead) {
		retval = -ENODEV;
		goto out;
	}

	client = kzalloc(sizeof(struct serio_raw_client), GFP_KERNEL);
	if (!client) {
		retval = -ENOMEM;
		goto out;
	}

	client->serio_raw = serio_raw;
	file->private_data = client;

	kref_get(&serio_raw->kref);

	serio_pause_rx(serio_raw->serio);
	list_add_tail(&client->node, &serio_raw->client_list);
	serio_continue_rx(serio_raw->serio);

out:
	mutex_unlock(&serio_raw_mutex);
	return retval;
}