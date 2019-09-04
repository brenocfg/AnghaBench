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
struct v4l2_subdev {int dummy; } ;
struct adv76xx_state {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_termination ) (struct v4l2_subdev*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi_write_clr_set (struct v4l2_subdev*,int,int,int) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_subdev*,int) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void disable_input(struct v4l2_subdev *sd)
{
	struct adv76xx_state *state = to_state(sd);

	hdmi_write_clr_set(sd, 0x1a, 0x10, 0x10); /* Mute audio */
	msleep(16); /* 512 samples with >= 32 kHz sample rate [REF_03, c. 7.16.10] */
	io_write(sd, 0x15, 0xbe);   /* Tristate all outputs from video core */
	state->info->set_termination(sd, false);
}