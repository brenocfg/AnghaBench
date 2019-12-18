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
struct v4l2_tuner {scalar_t__ index; scalar_t__ type; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct cx18 {int dummy; } ;
struct TYPE_2__ {struct cx18* cx; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  cx18_call_all (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 TYPE_1__* fh2id (void*) ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tuner ; 

__attribute__((used)) static int cx18_g_tuner(struct file *file, void *fh, struct v4l2_tuner *vt)
{
	struct cx18 *cx = fh2id(fh)->cx;

	if (vt->index != 0)
		return -EINVAL;

	cx18_call_all(cx, tuner, g_tuner, vt);

	if (vt->type == V4L2_TUNER_RADIO)
		strscpy(vt->name, "cx18 Radio Tuner", sizeof(vt->name));
	else
		strscpy(vt->name, "cx18 TV Tuner", sizeof(vt->name));
	return 0;
}