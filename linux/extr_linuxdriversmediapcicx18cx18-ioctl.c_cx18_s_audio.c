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
struct v4l2_audio {scalar_t__ index; } ;
struct file {int dummy; } ;
struct cx18 {scalar_t__ nof_audio_inputs; scalar_t__ audio_input; } ;
struct TYPE_2__ {struct cx18* cx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cx18_audio_set_io (struct cx18*) ; 
 TYPE_1__* fh2id (void*) ; 

__attribute__((used)) static int cx18_s_audio(struct file *file, void *fh, const struct v4l2_audio *vout)
{
	struct cx18 *cx = fh2id(fh)->cx;

	if (vout->index >= cx->nof_audio_inputs)
		return -EINVAL;
	cx->audio_input = vout->index;
	cx18_audio_set_io(cx);
	return 0;
}