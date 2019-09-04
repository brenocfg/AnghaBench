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
struct smu_private {int /*<<< orphan*/  list; int /*<<< orphan*/  wait; int /*<<< orphan*/  mode; int /*<<< orphan*/  lock; } ;
struct inode {int dummy; } ;
struct file {struct smu_private* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct smu_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smu_clist ; 
 int /*<<< orphan*/  smu_clist_lock ; 
 int /*<<< orphan*/  smu_file_commands ; 
 int /*<<< orphan*/  smu_mutex ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int smu_open(struct inode *inode, struct file *file)
{
	struct smu_private *pp;
	unsigned long flags;

	pp = kzalloc(sizeof(struct smu_private), GFP_KERNEL);
	if (pp == 0)
		return -ENOMEM;
	spin_lock_init(&pp->lock);
	pp->mode = smu_file_commands;
	init_waitqueue_head(&pp->wait);

	mutex_lock(&smu_mutex);
	spin_lock_irqsave(&smu_clist_lock, flags);
	list_add(&pp->list, &smu_clist);
	spin_unlock_irqrestore(&smu_clist_lock, flags);
	file->private_data = pp;
	mutex_unlock(&smu_mutex);

	return 0;
}