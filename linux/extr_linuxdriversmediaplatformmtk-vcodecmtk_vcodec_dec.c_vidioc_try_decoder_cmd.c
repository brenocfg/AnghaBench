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
struct v4l2_decoder_cmd {int cmd; int /*<<< orphan*/  flags; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_DEC_CMD_START 129 
#define  V4L2_DEC_CMD_STOP 128 
 int /*<<< orphan*/  mtk_v4l2_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_try_decoder_cmd(struct file *file, void *priv,
				struct v4l2_decoder_cmd *cmd)
{
	switch (cmd->cmd) {
	case V4L2_DEC_CMD_STOP:
	case V4L2_DEC_CMD_START:
		if (cmd->flags != 0) {
			mtk_v4l2_err("cmd->flags=%u", cmd->flags);
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}