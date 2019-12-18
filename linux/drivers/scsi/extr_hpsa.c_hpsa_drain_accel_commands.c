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
struct ctlr_info {int nr_cmds; struct CommandList* cmd_pool; } ;
struct CommandList {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmd_free (struct ctlr_info*,struct CommandList*) ; 
 scalar_t__ is_accelerated_cmd (struct CommandList*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void hpsa_drain_accel_commands(struct ctlr_info *h)
{
	struct CommandList *c = NULL;
	int i, accel_cmds_out;
	int refcount;

	do { /* wait for all outstanding ioaccel commands to drain out */
		accel_cmds_out = 0;
		for (i = 0; i < h->nr_cmds; i++) {
			c = h->cmd_pool + i;
			refcount = atomic_inc_return(&c->refcount);
			if (refcount > 1) /* Command is allocated */
				accel_cmds_out += is_accelerated_cmd(c);
			cmd_free(h, c);
		}
		if (accel_cmds_out <= 0)
			break;
		msleep(100);
	} while (1);
}