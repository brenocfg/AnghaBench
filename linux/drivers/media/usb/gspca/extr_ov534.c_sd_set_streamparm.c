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
struct sd {int frame_rate; } ;
struct gspca_dev {scalar_t__ streaming; } ;

/* Variables and functions */
 int DEFAULT_FRAME_RATE ; 
 int /*<<< orphan*/  set_frame_rate (struct gspca_dev*) ; 

__attribute__((used)) static void sd_set_streamparm(struct gspca_dev *gspca_dev,
			     struct v4l2_streamparm *parm)
{
	struct v4l2_captureparm *cp = &parm->parm.capture;
	struct v4l2_fract *tpf = &cp->timeperframe;
	struct sd *sd = (struct sd *) gspca_dev;

	if (tpf->numerator == 0 || tpf->denominator == 0)
		sd->frame_rate = DEFAULT_FRAME_RATE;
	else
		sd->frame_rate = tpf->denominator / tpf->numerator;

	if (gspca_dev->streaming)
		set_frame_rate(gspca_dev);

	/* Return the actual framerate */
	tpf->numerator = 1;
	tpf->denominator = sd->frame_rate;
}