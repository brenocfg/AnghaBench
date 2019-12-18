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
struct v4l2_encoder_cmd {int cmd; } ;
struct file {int dummy; } ;
struct allegro_channel {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_ENC_CMD_START 129 
#define  V4L2_ENC_CMD_STOP 128 
 int allegro_channel_cmd_start (struct allegro_channel*) ; 
 int allegro_channel_cmd_stop (struct allegro_channel*) ; 
 struct allegro_channel* fh_to_channel (void*) ; 
 int v4l2_m2m_ioctl_try_encoder_cmd (struct file*,void*,struct v4l2_encoder_cmd*) ; 

__attribute__((used)) static int allegro_encoder_cmd(struct file *file, void *fh,
			       struct v4l2_encoder_cmd *cmd)
{
	struct allegro_channel *channel = fh_to_channel(fh);
	int err;

	err = v4l2_m2m_ioctl_try_encoder_cmd(file, fh, cmd);
	if (err)
		return err;

	switch (cmd->cmd) {
	case V4L2_ENC_CMD_STOP:
		err = allegro_channel_cmd_stop(channel);
		break;
	case V4L2_ENC_CMD_START:
		err = allegro_channel_cmd_start(channel);
		break;
	default:
		err = -EINVAL;
		break;
	}

	return err;
}