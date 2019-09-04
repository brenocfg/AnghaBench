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
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } ;
struct TYPE_3__ {scalar_t__ vfl_dir; } ;
struct ivtv_stream {TYPE_1__ vdev; } ;
struct ivtv {struct ivtv_stream* streams; } ;
struct file {int dummy; } ;
struct TYPE_4__ {size_t type; struct ivtv* itv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* fh2id (void*) ; 
 int /*<<< orphan*/  ivtv_call_all (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency const*) ; 
 int /*<<< orphan*/  ivtv_mute (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_unmute (struct ivtv*) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 

int ivtv_s_frequency(struct file *file, void *fh, const struct v4l2_frequency *vf)
{
	struct ivtv *itv = fh2id(fh)->itv;
	struct ivtv_stream *s = &itv->streams[fh2id(fh)->type];

	if (s->vdev.vfl_dir)
		return -ENOTTY;
	if (vf->tuner != 0)
		return -EINVAL;

	ivtv_mute(itv);
	IVTV_DEBUG_INFO("v4l2 ioctl: set frequency %d\n", vf->frequency);
	ivtv_call_all(itv, tuner, s_frequency, vf);
	ivtv_unmute(itv);
	return 0;
}