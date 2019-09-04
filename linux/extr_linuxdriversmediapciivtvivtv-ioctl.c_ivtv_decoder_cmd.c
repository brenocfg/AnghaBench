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
struct v4l2_decoder_cmd {int /*<<< orphan*/  cmd; } ;
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_IOCTL (char*,int /*<<< orphan*/ ) ; 
 struct ivtv_open_id* fh2id (int /*<<< orphan*/ ) ; 
 int ivtv_video_command (struct ivtv*,struct ivtv_open_id*,struct v4l2_decoder_cmd*,int) ; 

__attribute__((used)) static int ivtv_decoder_cmd(struct file *file, void *fh, struct v4l2_decoder_cmd *dec)
{
	struct ivtv_open_id *id = fh2id(file->private_data);
	struct ivtv *itv = id->itv;

	IVTV_DEBUG_IOCTL("VIDIOC_DECODER_CMD %d\n", dec->cmd);
	return ivtv_video_command(itv, id, dec, false);
}