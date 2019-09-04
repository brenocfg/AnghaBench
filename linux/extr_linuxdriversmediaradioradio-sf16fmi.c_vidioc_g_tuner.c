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
struct v4l2_tuner {scalar_t__ index; int rxsubchans; int capability; int /*<<< orphan*/  signal; int /*<<< orphan*/  audmode; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct fmi {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RSF16_MAXFREQ ; 
 int /*<<< orphan*/  RSF16_MINFREQ ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  fmi_getsigstr (struct fmi*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct fmi* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_tuner(struct file *file, void *priv,
					struct v4l2_tuner *v)
{
	struct fmi *fmi = video_drvdata(file);

	if (v->index > 0)
		return -EINVAL;

	strlcpy(v->name, "FM", sizeof(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->rangelow = RSF16_MINFREQ;
	v->rangehigh = RSF16_MAXFREQ;
	v->rxsubchans = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO;
	v->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_LOW;
	v->audmode = V4L2_TUNER_MODE_STEREO;
	v->signal = fmi_getsigstr(fmi);
	return 0;
}