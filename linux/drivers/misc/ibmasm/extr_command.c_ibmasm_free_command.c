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
struct kref {int dummy; } ;
struct command {struct command* buffer; int /*<<< orphan*/  queue_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_count ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct command*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct command* to_command (struct kref*) ; 

void ibmasm_free_command(struct kref *kref)
{
	struct command *cmd = to_command(kref);

	list_del(&cmd->queue_node);
	atomic_dec(&command_count);
	dbg("command count: %d\n", atomic_read(&command_count));
	kfree(cmd->buffer);
	kfree(cmd);
}