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
struct v4l2_tuner {scalar_t__ index; int capability; int /*<<< orphan*/  type; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  name; } ;
struct saa7164_port {struct saa7164_dev* dev; } ;
struct saa7164_encoder_fh {struct saa7164_port* port; } ;
struct saa7164_dev {int dummy; } ;
struct file {struct saa7164_encoder_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGLVL_ENC ; 
 int EINVAL ; 
 int /*<<< orphan*/  SAA7164_TV_MAX_FREQ ; 
 int /*<<< orphan*/  SAA7164_TV_MIN_FREQ ; 
 int V4L2_TUNER_CAP_NORM ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

int saa7164_g_tuner(struct file *file, void *priv, struct v4l2_tuner *t)
{
	struct saa7164_encoder_fh *fh = file->private_data;
	struct saa7164_port *port = fh->port;
	struct saa7164_dev *dev = port->dev;

	if (0 != t->index)
		return -EINVAL;

	strscpy(t->name, "tuner", sizeof(t->name));
	t->capability = V4L2_TUNER_CAP_NORM | V4L2_TUNER_CAP_STEREO;
	t->rangelow = SAA7164_TV_MIN_FREQ;
	t->rangehigh = SAA7164_TV_MAX_FREQ;

	dprintk(DBGLVL_ENC, "VIDIOC_G_TUNER: tuner type %d\n", t->type);

	return 0;
}