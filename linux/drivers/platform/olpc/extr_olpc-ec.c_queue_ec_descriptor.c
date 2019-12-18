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
struct olpc_ec_priv {int /*<<< orphan*/  worker; int /*<<< orphan*/  cmd_q_lock; int /*<<< orphan*/  cmd_q; } ;
struct ec_cmd_desc {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void queue_ec_descriptor(struct ec_cmd_desc *desc,
		struct olpc_ec_priv *ec)
{
	unsigned long flags;

	INIT_LIST_HEAD(&desc->node);

	spin_lock_irqsave(&ec->cmd_q_lock, flags);
	list_add_tail(&desc->node, &ec->cmd_q);
	spin_unlock_irqrestore(&ec->cmd_q_lock, flags);

	schedule_work(&ec->worker);
}