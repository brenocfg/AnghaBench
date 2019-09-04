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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_tuner {scalar_t__ index; scalar_t__ audmode; int rxsubchans; } ;
struct fmdev {scalar_t__ curr_fmmode; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FM_MODE_RX ; 
 int /*<<< orphan*/  FM_MONO_MODE ; 
 int /*<<< orphan*/  FM_RDS_DISABLE ; 
 int /*<<< orphan*/  FM_RDS_ENABLE ; 
 int /*<<< orphan*/  FM_STEREO_MODE ; 
 scalar_t__ V4L2_TUNER_MODE_STEREO ; 
 int V4L2_TUNER_SUB_RDS ; 
 int fmc_set_mode (struct fmdev*,scalar_t__) ; 
 int fmc_set_rds_mode (struct fmdev*,int /*<<< orphan*/ ) ; 
 int fmc_set_stereo_mono (struct fmdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmerr (char*) ; 
 struct fmdev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fm_v4l2_vidioc_s_tuner(struct file *file, void *priv,
		const struct v4l2_tuner *tuner)
{
	struct fmdev *fmdev = video_drvdata(file);
	u16 aud_mode;
	u8 rds_mode;
	int ret;

	if (tuner->index != 0)
		return -EINVAL;

	aud_mode = (tuner->audmode == V4L2_TUNER_MODE_STEREO) ?
			FM_STEREO_MODE : FM_MONO_MODE;
	rds_mode = (tuner->rxsubchans & V4L2_TUNER_SUB_RDS) ?
			FM_RDS_ENABLE : FM_RDS_DISABLE;

	if (fmdev->curr_fmmode != FM_MODE_RX) {
		ret = fmc_set_mode(fmdev, FM_MODE_RX);
		if (ret < 0) {
			fmerr("Failed to set RX mode\n");
			return ret;
		}
	}

	ret = fmc_set_stereo_mono(fmdev, aud_mode);
	if (ret < 0) {
		fmerr("Failed to set RX stereo/mono mode\n");
		return ret;
	}

	ret = fmc_set_rds_mode(fmdev, rds_mode);
	if (ret < 0)
		fmerr("Failed to set RX RDS mode\n");

	return ret;
}