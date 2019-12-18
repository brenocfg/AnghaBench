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
struct ivtv {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct ivtv* itv; } ;

/* Variables and functions */
 TYPE_1__* fh2id (void*) ; 
 int ivtv_get_audio_input (struct ivtv*,int /*<<< orphan*/ ,struct v4l2_audio*) ; 

__attribute__((used)) static int ivtv_enumaudio(struct file *file, void *fh, struct v4l2_audio *vin)
{
	struct ivtv *itv = fh2id(fh)->itv;

	return ivtv_get_audio_input(itv, vin->index, vin);
}