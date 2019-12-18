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
struct v4l2_tuner {scalar_t__ index; int capability; int /*<<< orphan*/  audmode; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct tm6000_fh {struct tm6000_core* dev; } ;
struct tm6000_core {int /*<<< orphan*/  v4l2_dev; } ;
struct file {struct tm6000_fh* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  memset (struct v4l2_tuner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 

__attribute__((used)) static int radio_g_tuner(struct file *file, void *priv,
					struct v4l2_tuner *t)
{
	struct tm6000_fh *fh = file->private_data;
	struct tm6000_core *dev = fh->dev;

	if (0 != t->index)
		return -EINVAL;

	memset(t, 0, sizeof(*t));
	strscpy(t->name, "Radio", sizeof(t->name));
	t->type = V4L2_TUNER_RADIO;
	t->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO;
	t->rxsubchans = V4L2_TUNER_SUB_STEREO;
	t->audmode = V4L2_TUNER_MODE_STEREO;

	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, g_tuner, t);

	return 0;
}