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
struct goldfish_pipe {TYPE_2__* command_buffer; TYPE_1__* dev; int /*<<< orphan*/  id; } ;
typedef  enum PipeCmdCode { ____Placeholder_PipeCmdCode } PipeCmdCode ;
struct TYPE_4__ {int cmd; int status; } ;
struct TYPE_3__ {scalar_t__ base; } ;

/* Variables and functions */
 int PIPE_ERROR_INVAL ; 
 scalar_t__ PIPE_REG_CMD ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int goldfish_pipe_cmd_locked(struct goldfish_pipe *pipe,
				    enum PipeCmdCode cmd)
{
	pipe->command_buffer->cmd = cmd;
	/* failure by default */
	pipe->command_buffer->status = PIPE_ERROR_INVAL;
	writel(pipe->id, pipe->dev->base + PIPE_REG_CMD);
	return pipe->command_buffer->status;
}