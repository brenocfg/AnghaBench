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
struct hpsa_scsi_dev_t {int /*<<< orphan*/  scsi3addr; } ;
struct ctlr_info {int nr_cmds; int /*<<< orphan*/  lock; struct CommandList* cmd_pool; } ;
struct CommandList {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmd_free (struct ctlr_info*,struct CommandList*) ; 
 scalar_t__ hpsa_cmd_dev_match (struct ctlr_info*,struct CommandList*,struct hpsa_scsi_dev_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_is_cmd_idle (struct CommandList*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hpsa_find_outstanding_commands_for_dev(struct ctlr_info *h,
						struct hpsa_scsi_dev_t *dev)
{
	int i;
	int count = 0;

	for (i = 0; i < h->nr_cmds; i++) {
		struct CommandList *c = h->cmd_pool + i;
		int refcount = atomic_inc_return(&c->refcount);

		if (refcount > 1 && hpsa_cmd_dev_match(h, c, dev,
				dev->scsi3addr)) {
			unsigned long flags;

			spin_lock_irqsave(&h->lock, flags);	/* Implied MB */
			if (!hpsa_is_cmd_idle(c))
				++count;
			spin_unlock_irqrestore(&h->lock, flags);
		}

		cmd_free(h, c);
	}

	return count;
}