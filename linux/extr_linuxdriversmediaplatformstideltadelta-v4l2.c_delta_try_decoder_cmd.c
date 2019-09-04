#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pts; } ;
struct v4l2_decoder_cmd {scalar_t__ cmd; int flags; TYPE_1__ stop; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_DEC_CMD_STOP ; 
 int V4L2_DEC_CMD_STOP_IMMEDIATELY ; 
 int V4L2_DEC_CMD_STOP_TO_BLACK ; 

__attribute__((used)) static int delta_try_decoder_cmd(struct file *file, void *fh,
				 struct v4l2_decoder_cmd *cmd)
{
	if (cmd->cmd != V4L2_DEC_CMD_STOP)
		return -EINVAL;

	if (cmd->flags & V4L2_DEC_CMD_STOP_TO_BLACK)
		return -EINVAL;

	if (!(cmd->flags & V4L2_DEC_CMD_STOP_IMMEDIATELY) &&
	    (cmd->stop.pts != 0))
		return -EINVAL;

	return 0;
}