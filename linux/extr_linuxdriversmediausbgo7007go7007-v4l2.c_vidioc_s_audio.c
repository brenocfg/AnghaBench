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
struct v4l2_audio {scalar_t__ index; } ;
struct go7007 {size_t aud_input; TYPE_1__* board_info; int /*<<< orphan*/  sd_audio; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  audio_input; } ;
struct TYPE_3__ {scalar_t__ num_aud_inputs; TYPE_2__* aud_inputs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  audio ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct go7007* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_audio(struct file *file, void *fh,
	const struct v4l2_audio *a)
{
	struct go7007 *go = video_drvdata(file);

	if (a->index >= go->board_info->num_aud_inputs)
		return -EINVAL;
	go->aud_input = a->index;
	v4l2_subdev_call(go->sd_audio, audio, s_routing,
		go->board_info->aud_inputs[go->aud_input].audio_input, 0, 0);
	return 0;
}