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
struct venus_inst {scalar_t__ codec_state; int /*<<< orphan*/  lock; scalar_t__ streamon_cap; scalar_t__ streamon_out; } ;
struct v4l2_decoder_cmd {scalar_t__ cmd; } ;
struct hfi_frame_data {int device_addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  buffer_type; int /*<<< orphan*/  member_0; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_BUFFERFLAG_EOS ; 
 int /*<<< orphan*/  HFI_BUFFER_INPUT ; 
 scalar_t__ V4L2_DEC_CMD_STOP ; 
 scalar_t__ VENUS_DEC_STATE_DECODING ; 
 scalar_t__ VENUS_DEC_STATE_DRAIN ; 
 int hfi_session_process_buf (struct venus_inst*,struct hfi_frame_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct venus_inst* to_inst (struct file*) ; 
 int v4l2_m2m_ioctl_try_decoder_cmd (struct file*,void*,struct v4l2_decoder_cmd*) ; 

__attribute__((used)) static int
vdec_decoder_cmd(struct file *file, void *fh, struct v4l2_decoder_cmd *cmd)
{
	struct venus_inst *inst = to_inst(file);
	struct hfi_frame_data fdata = {0};
	int ret;

	ret = v4l2_m2m_ioctl_try_decoder_cmd(file, fh, cmd);
	if (ret)
		return ret;

	mutex_lock(&inst->lock);

	if (cmd->cmd == V4L2_DEC_CMD_STOP) {
		/*
		 * Implement V4L2_DEC_CMD_STOP by enqueue an empty buffer on
		 * decoder input to signal EOS.
		 */
		if (!(inst->streamon_out && inst->streamon_cap))
			goto unlock;

		fdata.buffer_type = HFI_BUFFER_INPUT;
		fdata.flags |= HFI_BUFFERFLAG_EOS;
		fdata.device_addr = 0xdeadb000;

		ret = hfi_session_process_buf(inst, &fdata);

		if (!ret && inst->codec_state == VENUS_DEC_STATE_DECODING)
			inst->codec_state = VENUS_DEC_STATE_DRAIN;
	}

unlock:
	mutex_unlock(&inst->lock);
	return ret;
}