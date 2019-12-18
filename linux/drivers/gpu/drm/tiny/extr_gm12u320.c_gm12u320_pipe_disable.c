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
struct gm12u320_device {int pipe_enabled; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct drm_simple_display_pipe {TYPE_2__ crtc; } ;
struct TYPE_3__ {struct gm12u320_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  gm12u320_stop_fb_update (struct gm12u320_device*) ; 

__attribute__((used)) static void gm12u320_pipe_disable(struct drm_simple_display_pipe *pipe)
{
	struct gm12u320_device *gm12u320 = pipe->crtc.dev->dev_private;

	gm12u320_stop_fb_update(gm12u320);
	gm12u320->pipe_enabled = false;
}