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
struct goldfish_pipe {int /*<<< orphan*/  lock; } ;
typedef  enum PipeCmdCode { ____Placeholder_PipeCmdCode } PipeCmdCode ;

/* Variables and functions */
 int PIPE_ERROR_IO ; 
 int goldfish_pipe_cmd_locked (struct goldfish_pipe*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int goldfish_pipe_cmd(struct goldfish_pipe *pipe, enum PipeCmdCode cmd)
{
	int status;

	if (mutex_lock_interruptible(&pipe->lock))
		return PIPE_ERROR_IO;
	status = goldfish_pipe_cmd_locked(pipe, cmd);
	mutex_unlock(&pipe->lock);
	return status;
}