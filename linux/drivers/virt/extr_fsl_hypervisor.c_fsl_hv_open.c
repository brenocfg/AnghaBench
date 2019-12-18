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
struct file {struct doorbell_queue* private_data; } ;
struct doorbell_queue {int /*<<< orphan*/  list; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  db_list ; 
 int /*<<< orphan*/  db_list_lock ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct doorbell_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fsl_hv_open(struct inode *inode, struct file *filp)
{
	struct doorbell_queue *dbq;
	unsigned long flags;
	int ret = 0;

	dbq = kzalloc(sizeof(struct doorbell_queue), GFP_KERNEL);
	if (!dbq) {
		pr_err("fsl-hv: out of memory\n");
		return -ENOMEM;
	}

	spin_lock_init(&dbq->lock);
	init_waitqueue_head(&dbq->wait);

	spin_lock_irqsave(&db_list_lock, flags);
	list_add(&dbq->list, &db_list);
	spin_unlock_irqrestore(&db_list_lock, flags);

	filp->private_data = dbq;

	return ret;
}