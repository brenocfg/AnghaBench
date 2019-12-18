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
struct v4l2_audio {size_t index; int /*<<< orphan*/  name; int /*<<< orphan*/  capability; } ;
struct TYPE_2__ {size_t audio_input; } ;
struct hdpvr_device {TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/ * audio_iname ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_audio(struct file *file, void *private_data,
			  struct v4l2_audio *audio)
{
	struct hdpvr_device *dev = video_drvdata(file);

	audio->index = dev->options.audio_input;
	audio->capability = V4L2_AUDCAP_STEREO;
	strscpy(audio->name, audio_iname[audio->index], sizeof(audio->name));
	return 0;
}