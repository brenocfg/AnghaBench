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
struct v4l2_audio {int /*<<< orphan*/  capability; int /*<<< orphan*/  name; scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int pvr2_g_audio(struct file *file, void *priv, struct v4l2_audio *vin)
{
	/* pkt: FIXME: see above comment (VIDIOC_ENUMAUDIO) */
	vin->index = 0;
	strscpy(vin->name, "PVRUSB2 Audio", sizeof(vin->name));
	vin->capability = V4L2_AUDCAP_STEREO;
	return 0;
}