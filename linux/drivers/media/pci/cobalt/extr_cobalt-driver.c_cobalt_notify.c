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
struct v4l2_subdev {int /*<<< orphan*/  v4l2_dev; } ;
struct cobalt_stream {int /*<<< orphan*/  vdev; scalar_t__ is_output; } ;
struct cobalt {struct cobalt_stream* streams; } ;

/* Variables and functions */
#define  ADV76XX_HOTPLUG 129 
 int /*<<< orphan*/  COBALT_SYS_CTRL_HPD_TO_CONNECTOR_BIT (unsigned int) ; 
#define  V4L2_DEVICE_NOTIFY_EVENT 128 
 int /*<<< orphan*/  cobalt_dbg (int,char*,unsigned int,...) ; 
 unsigned int cobalt_get_sd_nr (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  cobalt_s_bit_sysctrl (struct cobalt*,int /*<<< orphan*/ ,int) ; 
 struct cobalt* to_cobalt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_event_queue (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void cobalt_notify(struct v4l2_subdev *sd,
			  unsigned int notification, void *arg)
{
	struct cobalt *cobalt = to_cobalt(sd->v4l2_dev);
	unsigned sd_nr = cobalt_get_sd_nr(sd);
	struct cobalt_stream *s = &cobalt->streams[sd_nr];
	bool hotplug = arg ? *((int *)arg) : false;

	if (s->is_output)
		return;

	switch (notification) {
	case ADV76XX_HOTPLUG:
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_HPD_TO_CONNECTOR_BIT(sd_nr), hotplug);
		cobalt_dbg(1, "Set hotplug for adv %d to %d\n", sd_nr, hotplug);
		break;
	case V4L2_DEVICE_NOTIFY_EVENT:
		cobalt_dbg(1, "Format changed for adv %d\n", sd_nr);
		v4l2_event_queue(&s->vdev, arg);
		break;
	default:
		break;
	}
}