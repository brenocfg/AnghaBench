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
typedef  int /*<<< orphan*/  u32 ;
struct c4iw_rdev {int dummy; } ;
struct c4iw_qid_list {int /*<<< orphan*/  entry; int /*<<< orphan*/  qid; } ;
struct c4iw_dev_ucontext {int /*<<< orphan*/  lock; int /*<<< orphan*/  qpids; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct c4iw_qid_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

void c4iw_put_qpid(struct c4iw_rdev *rdev, u32 qid,
		   struct c4iw_dev_ucontext *uctx)
{
	struct c4iw_qid_list *entry;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return;
	pr_debug("qid 0x%x\n", qid);
	entry->qid = qid;
	mutex_lock(&uctx->lock);
	list_add_tail(&entry->entry, &uctx->qpids);
	mutex_unlock(&uctx->lock);
}