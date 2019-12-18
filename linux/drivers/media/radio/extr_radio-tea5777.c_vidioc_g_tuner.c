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
struct v4l2_tuner {scalar_t__ index; int capability; int signal; int /*<<< orphan*/  audmode; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct radio_tea5777 {size_t band; int read_reg; int /*<<< orphan*/  audmode; scalar_t__ has_am; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; } ;

/* Variables and functions */
 size_t BAND_AM ; 
 size_t BAND_FM ; 
 int EINVAL ; 
 int TEA5777_R_FM_STEREO_MASK ; 
 int TEA5777_R_LEVEL_MASK ; 
 int TEA5777_R_LEVEL_SHIFT ; 
 int V4L2_TUNER_CAP_FREQ_BANDS ; 
 int V4L2_TUNER_CAP_HWSEEK_BOUNDED ; 
 int V4L2_TUNER_CAP_HWSEEK_PROG_LIM ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 TYPE_1__* bands ; 
 int /*<<< orphan*/  memset (struct v4l2_tuner*,int /*<<< orphan*/ ,int) ; 
 int radio_tea5777_update_read_reg (struct radio_tea5777*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct radio_tea5777* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_tuner(struct file *file, void *priv,
					struct v4l2_tuner *v)
{
	struct radio_tea5777 *tea = video_drvdata(file);
	int res;

	if (v->index > 0)
		return -EINVAL;

	res = radio_tea5777_update_read_reg(tea, 0);
	if (res)
		return res;

	memset(v, 0, sizeof(*v));
	if (tea->has_am)
		strscpy(v->name, "AM/FM", sizeof(v->name));
	else
		strscpy(v->name, "FM", sizeof(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			V4L2_TUNER_CAP_FREQ_BANDS |
			V4L2_TUNER_CAP_HWSEEK_BOUNDED |
			V4L2_TUNER_CAP_HWSEEK_PROG_LIM;
	v->rangelow   = tea->has_am ? bands[BAND_AM].rangelow :
				      bands[BAND_FM].rangelow;
	v->rangehigh  = bands[BAND_FM].rangehigh;
	if (tea->band == BAND_FM &&
			(tea->read_reg & TEA5777_R_FM_STEREO_MASK))
		v->rxsubchans = V4L2_TUNER_SUB_STEREO;
	else
		v->rxsubchans = V4L2_TUNER_SUB_MONO;
	v->audmode = tea->audmode;
	/* shift - 12 to convert 4-bits (0-15) scale to 16-bits (0-65535) */
	v->signal = (tea->read_reg & TEA5777_R_LEVEL_MASK) >>
		    (TEA5777_R_LEVEL_SHIFT - 12);

	/* Invalidate read_reg, so that next call we return up2date signal */
	tea->read_reg = -1;

	return 0;
}