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
struct v4l2_subdev {int dummy; } ;
struct cx18 {TYPE_2__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  radio; int /*<<< orphan*/  mask; } ;
struct TYPE_4__ {TYPE_1__ gpio_audio_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_update (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int gpiomux_s_radio(struct v4l2_subdev *sd)
{
	struct cx18 *cx = v4l2_get_subdevdata(sd);

	/*
	 * FIXME - work out the cx->active/audio_input mess - this is
	 * intended to handle the switch to radio mode and set the
	 * audio routing, but we need to update the state in cx
	 */
	gpio_update(cx, cx->card->gpio_audio_input.mask,
			cx->card->gpio_audio_input.radio);
	return 0;
}