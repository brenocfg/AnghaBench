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
struct v4l2_modulator {scalar_t__ index; int txsubchans; int capability; } ;
struct TYPE_4__ {scalar_t__ flag; } ;
struct TYPE_3__ {scalar_t__ aud_mode; TYPE_2__ rds; } ;
struct fmdev {scalar_t__ curr_fmmode; TYPE_1__ tx_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ FM_MODE_TX ; 
 scalar_t__ FM_RDS_ENABLE ; 
 scalar_t__ FM_STEREO_MODE ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_RDS ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_RDS ; 
 int V4L2_TUNER_SUB_STEREO ; 
 struct fmdev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fm_v4l2_vidioc_g_modulator(struct file *file, void *priv,
		struct v4l2_modulator *mod)
{
	struct fmdev *fmdev = video_drvdata(file);

	if (mod->index != 0)
		return -EINVAL;

	if (fmdev->curr_fmmode != FM_MODE_TX)
		return -EPERM;

	mod->txsubchans = ((fmdev->tx_data.aud_mode == FM_STEREO_MODE) ?
				V4L2_TUNER_SUB_STEREO : V4L2_TUNER_SUB_MONO) |
				((fmdev->tx_data.rds.flag == FM_RDS_ENABLE) ?
				V4L2_TUNER_SUB_RDS : 0);

	mod->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_RDS |
				V4L2_TUNER_CAP_LOW;

	return 0;
}