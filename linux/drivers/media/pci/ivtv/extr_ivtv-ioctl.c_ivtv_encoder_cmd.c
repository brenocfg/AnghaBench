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
struct v4l2_encoder_cmd {int cmd; int flags; } ;
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  i_flags; int /*<<< orphan*/  capturing; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_PAUSE_ENCODER ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  IVTV_DEBUG_IOCTL (char*,...) ; 
 int /*<<< orphan*/  IVTV_F_I_ENC_PAUSED ; 
#define  V4L2_ENC_CMD_PAUSE 131 
#define  V4L2_ENC_CMD_RESUME 130 
#define  V4L2_ENC_CMD_START 129 
#define  V4L2_ENC_CMD_STOP 128 
 int V4L2_ENC_CMD_STOP_AT_GOP_END ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct ivtv_open_id* fh2id (void*) ; 
 int /*<<< orphan*/  ivtv_mute (struct ivtv*) ; 
 int ivtv_start_capture (struct ivtv_open_id*) ; 
 int /*<<< orphan*/  ivtv_stop_capture (struct ivtv_open_id*,int) ; 
 int /*<<< orphan*/  ivtv_unmute (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ivtv_encoder_cmd(struct file *file, void *fh, struct v4l2_encoder_cmd *enc)
{
	struct ivtv_open_id *id = fh2id(fh);
	struct ivtv *itv = id->itv;


	switch (enc->cmd) {
	case V4L2_ENC_CMD_START:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_START\n");
		enc->flags = 0;
		return ivtv_start_capture(id);

	case V4L2_ENC_CMD_STOP:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_STOP\n");
		enc->flags &= V4L2_ENC_CMD_STOP_AT_GOP_END;
		ivtv_stop_capture(id, enc->flags & V4L2_ENC_CMD_STOP_AT_GOP_END);
		return 0;

	case V4L2_ENC_CMD_PAUSE:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_PAUSE\n");
		enc->flags = 0;

		if (!atomic_read(&itv->capturing))
			return -EPERM;
		if (test_and_set_bit(IVTV_F_I_ENC_PAUSED, &itv->i_flags))
			return 0;

		ivtv_mute(itv);
		ivtv_vapi(itv, CX2341X_ENC_PAUSE_ENCODER, 1, 0);
		break;

	case V4L2_ENC_CMD_RESUME:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_RESUME\n");
		enc->flags = 0;

		if (!atomic_read(&itv->capturing))
			return -EPERM;

		if (!test_and_clear_bit(IVTV_F_I_ENC_PAUSED, &itv->i_flags))
			return 0;

		ivtv_vapi(itv, CX2341X_ENC_PAUSE_ENCODER, 1, 1);
		ivtv_unmute(itv);
		break;
	default:
		IVTV_DEBUG_IOCTL("Unknown cmd %d\n", enc->cmd);
		return -EINVAL;
	}

	return 0;
}