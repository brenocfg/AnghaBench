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
struct notifier_block {int dummy; } ;
struct OpalMsgNode {int /*<<< orphan*/  list; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long OPAL_MSG_MEM_ERR ; 
 struct OpalMsgNode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_error_work ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  opal_mem_err_lock ; 
 int /*<<< orphan*/  opal_memory_err_list ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int opal_memory_err_event(struct notifier_block *nb,
			  unsigned long msg_type, void *msg)
{
	unsigned long flags;
	struct OpalMsgNode *msg_node;

	if (msg_type != OPAL_MSG_MEM_ERR)
		return 0;

	msg_node = kzalloc(sizeof(*msg_node), GFP_ATOMIC);
	if (!msg_node) {
		pr_err("MEMORY_ERROR: out of memory, Opal message event not"
		       "handled\n");
		return -ENOMEM;
	}
	memcpy(&msg_node->msg, msg, sizeof(msg_node->msg));

	spin_lock_irqsave(&opal_mem_err_lock, flags);
	list_add(&msg_node->list, &opal_memory_err_list);
	spin_unlock_irqrestore(&opal_mem_err_lock, flags);

	schedule_work(&mem_error_work);
	return 0;
}