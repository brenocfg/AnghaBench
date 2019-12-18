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
struct v4l2_tuner {scalar_t__ index; } ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cx18_call_all (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner const*) ; 
 struct cx18_open_id* fh2id (void*) ; 
 int /*<<< orphan*/  s_tuner ; 
 int /*<<< orphan*/  tuner ; 

__attribute__((used)) static int cx18_s_tuner(struct file *file, void *fh, const struct v4l2_tuner *vt)
{
	struct cx18_open_id *id = fh2id(fh);
	struct cx18 *cx = id->cx;

	if (vt->index != 0)
		return -EINVAL;

	cx18_call_all(cx, tuner, s_tuner, vt);
	return 0;
}