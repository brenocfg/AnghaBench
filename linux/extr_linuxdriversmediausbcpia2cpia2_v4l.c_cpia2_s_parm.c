#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fract {int /*<<< orphan*/  numerator; int /*<<< orphan*/  denominator; } ;
struct v4l2_captureparm {struct v4l2_fract timeperframe; } ;
struct TYPE_7__ {struct v4l2_captureparm capture; } ;
struct v4l2_streamparm {TYPE_1__ parm; } ;
struct file {int dummy; } ;
struct TYPE_9__ {scalar_t__ sensor_flags; } ;
struct TYPE_8__ {scalar_t__ device_type; } ;
struct TYPE_10__ {TYPE_3__ version; TYPE_2__ pnp_id; } ;
struct camera_data {TYPE_4__ params; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; struct v4l2_fract period; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 scalar_t__ CPIA2_VP_SENSOR_FLAGS_500 ; 
 scalar_t__ DEVICE_STV_672 ; 
 int cpia2_g_parm (struct file*,void*,struct v4l2_streamparm*) ; 
 int cpia2_set_fps (struct camera_data*,int /*<<< orphan*/ ) ; 
 TYPE_5__* framerate_controls ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_s_parm(struct file *file, void *fh, struct v4l2_streamparm *p)
{
	struct camera_data *cam = video_drvdata(file);
	struct v4l2_captureparm *cap = &p->parm.capture;
	struct v4l2_fract tpf = cap->timeperframe;
	int max = ARRAY_SIZE(framerate_controls) - 1;
	int ret;
	int i;

	ret = cpia2_g_parm(file, fh, p);
	if (ret || !tpf.denominator || !tpf.numerator)
		return ret;

	/* Maximum 15 fps for this model */
	if (cam->params.pnp_id.device_type == DEVICE_STV_672 &&
	    cam->params.version.sensor_flags == CPIA2_VP_SENSOR_FLAGS_500)
		max -= 2;
	for (i = 0; i <= max; i++) {
		struct v4l2_fract f1 = tpf;
		struct v4l2_fract f2 = framerate_controls[i].period;

		f1.numerator *= f2.denominator;
		f2.numerator *= f1.denominator;
		if (f1.numerator >= f2.numerator)
			break;
	}
	if (i > max)
		i = max;
	cap->timeperframe = framerate_controls[i].period;
	return cpia2_set_fps(cam, framerate_controls[i].value);
}