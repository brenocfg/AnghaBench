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
struct service_processor {int /*<<< orphan*/  lock; } ;
struct command {size_t buffer_size; int /*<<< orphan*/  queue_node; int /*<<< orphan*/  wait; int /*<<< orphan*/  status; int /*<<< orphan*/ * lock; int /*<<< orphan*/  kref; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IBMASM_CMD_MAX_BUFFER_SIZE ; 
 int /*<<< orphan*/  IBMASM_CMD_PENDING ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_count ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct command*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 

struct command *ibmasm_new_command(struct service_processor *sp, size_t buffer_size)
{
	struct command *cmd;

	if (buffer_size > IBMASM_CMD_MAX_BUFFER_SIZE)
		return NULL;

	cmd = kzalloc(sizeof(struct command), GFP_KERNEL);
	if (cmd == NULL)
		return NULL;


	cmd->buffer = kzalloc(buffer_size, GFP_KERNEL);
	if (cmd->buffer == NULL) {
		kfree(cmd);
		return NULL;
	}
	cmd->buffer_size = buffer_size;

	kref_init(&cmd->kref);
	cmd->lock = &sp->lock;

	cmd->status = IBMASM_CMD_PENDING;
	init_waitqueue_head(&cmd->wait);
	INIT_LIST_HEAD(&cmd->queue_node);

	atomic_inc(&command_count);
	dbg("command count: %d\n", atomic_read(&command_count));

	return cmd;
}