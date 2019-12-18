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
struct goldfish_pipe_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** pipes; } ;
struct goldfish_pipe {size_t id; scalar_t__ command_buffer; struct goldfish_pipe_dev* dev; } ;
struct file {struct goldfish_pipe* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_CMD_CLOSE ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  goldfish_pipe_cmd (struct goldfish_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct goldfish_pipe*) ; 
 int /*<<< orphan*/  signalled_pipes_remove_locked (struct goldfish_pipe_dev*,struct goldfish_pipe*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int goldfish_pipe_release(struct inode *inode, struct file *filp)
{
	unsigned long flags;
	struct goldfish_pipe *pipe = filp->private_data;
	struct goldfish_pipe_dev *dev = pipe->dev;

	/* The guest is closing the channel, so tell the emulator right now */
	goldfish_pipe_cmd(pipe, PIPE_CMD_CLOSE);

	spin_lock_irqsave(&dev->lock, flags);
	dev->pipes[pipe->id] = NULL;
	signalled_pipes_remove_locked(dev, pipe);
	spin_unlock_irqrestore(&dev->lock, flags);

	filp->private_data = NULL;
	free_page((unsigned long)pipe->command_buffer);
	kfree(pipe);
	return 0;
}