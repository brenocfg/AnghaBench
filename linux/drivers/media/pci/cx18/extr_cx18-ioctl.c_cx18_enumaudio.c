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
struct v4l2_audio {int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;
struct cx18 {int dummy; } ;
struct TYPE_2__ {struct cx18* cx; } ;

/* Variables and functions */
 int cx18_get_audio_input (struct cx18*,int /*<<< orphan*/ ,struct v4l2_audio*) ; 
 TYPE_1__* fh2id (void*) ; 

__attribute__((used)) static int cx18_enumaudio(struct file *file, void *fh, struct v4l2_audio *vin)
{
	struct cx18 *cx = fh2id(fh)->cx;

	return cx18_get_audio_input(cx, vin->index, vin);
}