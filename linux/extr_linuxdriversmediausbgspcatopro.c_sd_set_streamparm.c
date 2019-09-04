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
struct v4l2_fract {int numerator; int denominator; } ;
struct v4l2_captureparm {struct v4l2_fract timeperframe; } ;
struct TYPE_2__ {struct v4l2_captureparm capture; } ;
struct v4l2_streamparm {TYPE_1__ parm; } ;
struct sd {int framerate; } ;
struct gspca_dev {int /*<<< orphan*/  exposure; scalar_t__ streaming; } ;

/* Variables and functions */
 int DEFAULT_FRAME_RATE ; 
 int get_fr_idx (struct gspca_dev*) ; 
 int* rates ; 
 int* rates_6810 ; 
 int /*<<< orphan*/  setframerate (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_set_streamparm(struct gspca_dev *gspca_dev,
			     struct v4l2_streamparm *parm)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct v4l2_captureparm *cp = &parm->parm.capture;
	struct v4l2_fract *tpf = &cp->timeperframe;
	int fr, i;

	if (tpf->numerator == 0 || tpf->denominator == 0)
		sd->framerate = DEFAULT_FRAME_RATE;
	else
		sd->framerate = tpf->denominator / tpf->numerator;

	if (gspca_dev->streaming)
		setframerate(gspca_dev, v4l2_ctrl_g_ctrl(gspca_dev->exposure));

	/* Return the actual framerate */
	i = get_fr_idx(gspca_dev);
	if (i & 0x80)
		fr = rates_6810[7 - (i & 0x07)];
	else
		fr = rates[6 - i];
	tpf->numerator = 1;
	tpf->denominator = fr;
}