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
struct v4l2_audio {unsigned int index; int /*<<< orphan*/  name; int /*<<< orphan*/  capability; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int HDPVR_AUDIO_INPUTS ; 
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/ * audio_iname ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_enumaudio(struct file *file, void *priv,
				struct v4l2_audio *audio)
{
	unsigned int n;

	n = audio->index;
	if (n >= HDPVR_AUDIO_INPUTS)
		return -EINVAL;

	audio->capability = V4L2_AUDCAP_STEREO;

	strscpy(audio->name, audio_iname[n], sizeof(audio->name));

	return 0;
}