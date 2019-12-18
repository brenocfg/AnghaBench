#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct goldfish_pipe_dev {int /*<<< orphan*/  lock; struct goldfish_pipe** pipes; TYPE_2__* buffers; } ;
struct goldfish_pipe_command {int id; } ;
struct goldfish_pipe {int id; struct goldfish_pipe_command* command_buffer; int /*<<< orphan*/  wake_queue; int /*<<< orphan*/  lock; struct goldfish_pipe_dev* dev; } ;
struct file {struct goldfish_pipe* private_data; } ;
struct TYPE_3__ {scalar_t__ command_buffer_ptr; int /*<<< orphan*/  rw_params_max_count; } ;
struct TYPE_4__ {TYPE_1__ open_command_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_BUFFERS_PER_COMMAND ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PIPE_CMD_OPEN ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 scalar_t__ __pa (struct goldfish_pipe_command*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int get_free_pipe_id_locked (struct goldfish_pipe_dev*) ; 
 int goldfish_pipe_cmd_locked (struct goldfish_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct goldfish_pipe*) ; 
 struct goldfish_pipe* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct goldfish_pipe_dev* to_goldfish_pipe_dev (struct file*) ; 

__attribute__((used)) static int goldfish_pipe_open(struct inode *inode, struct file *file)
{
	struct goldfish_pipe_dev *dev = to_goldfish_pipe_dev(file);
	unsigned long flags;
	int id;
	int status;

	/* Allocate new pipe kernel object */
	struct goldfish_pipe *pipe = kzalloc(sizeof(*pipe), GFP_KERNEL);

	if (!pipe)
		return -ENOMEM;

	pipe->dev = dev;
	mutex_init(&pipe->lock);
	init_waitqueue_head(&pipe->wake_queue);

	/*
	 * Command buffer needs to be allocated on its own page to make sure
	 * it is physically contiguous in host's address space.
	 */
	BUILD_BUG_ON(sizeof(struct goldfish_pipe_command) > PAGE_SIZE);
	pipe->command_buffer =
		(struct goldfish_pipe_command *)__get_free_page(GFP_KERNEL);
	if (!pipe->command_buffer) {
		status = -ENOMEM;
		goto err_pipe;
	}

	spin_lock_irqsave(&dev->lock, flags);

	id = get_free_pipe_id_locked(dev);
	if (id < 0) {
		status = id;
		goto err_id_locked;
	}

	dev->pipes[id] = pipe;
	pipe->id = id;
	pipe->command_buffer->id = id;

	/* Now tell the emulator we're opening a new pipe. */
	dev->buffers->open_command_params.rw_params_max_count =
			MAX_BUFFERS_PER_COMMAND;
	dev->buffers->open_command_params.command_buffer_ptr =
			(u64)(unsigned long)__pa(pipe->command_buffer);
	status = goldfish_pipe_cmd_locked(pipe, PIPE_CMD_OPEN);
	spin_unlock_irqrestore(&dev->lock, flags);
	if (status < 0)
		goto err_cmd;
	/* All is done, save the pipe into the file's private data field */
	file->private_data = pipe;
	return 0;

err_cmd:
	spin_lock_irqsave(&dev->lock, flags);
	dev->pipes[id] = NULL;
err_id_locked:
	spin_unlock_irqrestore(&dev->lock, flags);
	free_page((unsigned long)pipe->command_buffer);
err_pipe:
	kfree(pipe);
	return status;
}