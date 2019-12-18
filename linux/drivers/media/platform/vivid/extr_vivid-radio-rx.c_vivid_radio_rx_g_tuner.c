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
struct vivid_dev {int radio_rx_hw_seek_mode; int radio_rx_sig_qual; scalar_t__ radio_rx_freq; int radio_tx_subchans; int /*<<< orphan*/  radio_rx_audmode; scalar_t__ radio_rx_rds_controls; scalar_t__ radio_rds_loop; scalar_t__ radio_rx_rds_enabled; scalar_t__ radio_rx_hw_seek_prog_lim; } ;
struct v4l2_tuner {scalar_t__ index; int capability; int signal; int afc; int rxsubchans; int /*<<< orphan*/  audmode; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_FREQ_RANGE_LOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  FM_FREQ_RANGE_HIGH ; 
 scalar_t__ FM_FREQ_RANGE_LOW ; 
 int V4L2_TUNER_CAP_FREQ_BANDS ; 
 int V4L2_TUNER_CAP_HWSEEK_BOUNDED ; 
 int V4L2_TUNER_CAP_HWSEEK_PROG_LIM ; 
 int V4L2_TUNER_CAP_HWSEEK_WRAP ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_RDS ; 
 int V4L2_TUNER_CAP_RDS_BLOCK_IO ; 
 int V4L2_TUNER_CAP_RDS_CONTROLS ; 
 int V4L2_TUNER_CAP_STEREO ; 
 void* V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_RDS ; 
 int V4L2_TUNER_SUB_STEREO ; 
#define  VIVID_HW_SEEK_BOTH 130 
#define  VIVID_HW_SEEK_BOUNDED 129 
#define  VIVID_HW_SEEK_WRAP 128 
 int abs (int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_radio_rds_init (struct vivid_dev*) ; 

int vivid_radio_rx_g_tuner(struct file *file, void *fh, struct v4l2_tuner *vt)
{
	struct vivid_dev *dev = video_drvdata(file);
	int delta = 800;
	int sig_qual;

	if (vt->index > 0)
		return -EINVAL;

	strscpy(vt->name, "AM/FM/SW Receiver", sizeof(vt->name));
	vt->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			 V4L2_TUNER_CAP_FREQ_BANDS | V4L2_TUNER_CAP_RDS |
			 (dev->radio_rx_rds_controls ?
				V4L2_TUNER_CAP_RDS_CONTROLS :
				V4L2_TUNER_CAP_RDS_BLOCK_IO) |
			 (dev->radio_rx_hw_seek_prog_lim ?
				V4L2_TUNER_CAP_HWSEEK_PROG_LIM : 0);
	switch (dev->radio_rx_hw_seek_mode) {
	case VIVID_HW_SEEK_BOUNDED:
		vt->capability |= V4L2_TUNER_CAP_HWSEEK_BOUNDED;
		break;
	case VIVID_HW_SEEK_WRAP:
		vt->capability |= V4L2_TUNER_CAP_HWSEEK_WRAP;
		break;
	case VIVID_HW_SEEK_BOTH:
		vt->capability |= V4L2_TUNER_CAP_HWSEEK_WRAP |
				  V4L2_TUNER_CAP_HWSEEK_BOUNDED;
		break;
	}
	vt->rangelow = AM_FREQ_RANGE_LOW;
	vt->rangehigh = FM_FREQ_RANGE_HIGH;
	sig_qual = dev->radio_rx_sig_qual;
	vt->signal = abs(sig_qual) > delta ? 0 :
		     0xffff - ((unsigned)abs(sig_qual) * 0xffff) / delta;
	vt->afc = sig_qual > delta ? 0 : sig_qual;
	if (abs(sig_qual) > delta)
		vt->rxsubchans = 0;
	else if (dev->radio_rx_freq < FM_FREQ_RANGE_LOW || vt->signal < 0x8000)
		vt->rxsubchans = V4L2_TUNER_SUB_MONO;
	else if (dev->radio_rds_loop && !(dev->radio_tx_subchans & V4L2_TUNER_SUB_STEREO))
		vt->rxsubchans = V4L2_TUNER_SUB_MONO;
	else
		vt->rxsubchans = V4L2_TUNER_SUB_STEREO;
	if (dev->radio_rx_rds_enabled &&
	    (!dev->radio_rds_loop || (dev->radio_tx_subchans & V4L2_TUNER_SUB_RDS)) &&
	    dev->radio_rx_freq >= FM_FREQ_RANGE_LOW && vt->signal >= 0xc000)
		vt->rxsubchans |= V4L2_TUNER_SUB_RDS;
	if (dev->radio_rx_rds_controls)
		vivid_radio_rds_init(dev);
	vt->audmode = dev->radio_rx_audmode;
	return 0;
}