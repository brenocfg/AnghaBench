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
typedef  int v4l2_std_id ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct TYPE_3__ {int count; int* start; } ;
struct TYPE_4__ {int width; int height; } ;
struct cx18 {int std; int is_60hz; int is_50hz; TYPE_1__ vbi; TYPE_2__ cxhdl; int /*<<< orphan*/  ana_capturing; int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,unsigned long long) ; 
 int /*<<< orphan*/  CX18_F_I_RADIO_USER ; 
 int EBUSY ; 
 int EINVAL ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_ALL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx18_call_all (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx2341x_handler_set_50hz (TYPE_2__*,int) ; 
 struct cx18_open_id* fh2id (void*) ; 
 int /*<<< orphan*/  s_std ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 

int cx18_s_std(struct file *file, void *fh, v4l2_std_id std)
{
	struct cx18_open_id *id = fh2id(fh);
	struct cx18 *cx = id->cx;

	if ((std & V4L2_STD_ALL) == 0)
		return -EINVAL;

	if (std == cx->std)
		return 0;

	if (test_bit(CX18_F_I_RADIO_USER, &cx->i_flags) ||
	    atomic_read(&cx->ana_capturing) > 0) {
		/* Switching standard would turn off the radio or mess
		   with already running streams, prevent that by
		   returning EBUSY. */
		return -EBUSY;
	}

	cx->std = std;
	cx->is_60hz = (std & V4L2_STD_525_60) ? 1 : 0;
	cx->is_50hz = !cx->is_60hz;
	cx2341x_handler_set_50hz(&cx->cxhdl, cx->is_50hz);
	cx->cxhdl.width = 720;
	cx->cxhdl.height = cx->is_50hz ? 576 : 480;
	cx->vbi.count = cx->is_50hz ? 18 : 12;
	cx->vbi.start[0] = cx->is_50hz ? 6 : 10;
	cx->vbi.start[1] = cx->is_50hz ? 318 : 273;
	CX18_DEBUG_INFO("Switching standard to %llx.\n",
			(unsigned long long) cx->std);

	/* Tuner */
	cx18_call_all(cx, video, s_std, cx->std);
	return 0;
}