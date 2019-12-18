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
struct v4l2_audio {size_t index; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; } ;
struct go7007 {size_t aud_input; TYPE_2__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* aud_inputs; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct go7007* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_audio(struct file *file, void *fh, struct v4l2_audio *a)
{
	struct go7007 *go = video_drvdata(file);

	a->index = go->aud_input;
	strscpy(a->name, go->board_info->aud_inputs[go->aud_input].name,
		sizeof(a->name));
	a->capability = V4L2_AUDCAP_STEREO;
	return 0;
}