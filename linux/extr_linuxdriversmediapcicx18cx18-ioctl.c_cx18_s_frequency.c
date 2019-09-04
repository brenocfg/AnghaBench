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
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cx18_call_all (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency const*) ; 
 int /*<<< orphan*/  cx18_mute (struct cx18*) ; 
 int /*<<< orphan*/  cx18_unmute (struct cx18*) ; 
 struct cx18_open_id* fh2id (void*) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 

int cx18_s_frequency(struct file *file, void *fh, const struct v4l2_frequency *vf)
{
	struct cx18_open_id *id = fh2id(fh);
	struct cx18 *cx = id->cx;

	if (vf->tuner != 0)
		return -EINVAL;

	cx18_mute(cx);
	CX18_DEBUG_INFO("v4l2 ioctl: set frequency %d\n", vf->frequency);
	cx18_call_all(cx, tuner, s_frequency, vf);
	cx18_unmute(cx);
	return 0;
}