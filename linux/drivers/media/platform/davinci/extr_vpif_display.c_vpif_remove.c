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
struct platform_device {int dummy; } ;
struct channel_obj {int /*<<< orphan*/  video_dev; } ;
struct TYPE_4__ {struct channel_obj** dev; int /*<<< orphan*/  sd; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  notifier; TYPE_1__* config; } ;
struct TYPE_3__ {scalar_t__ asd_sizes; } ;

/* Variables and functions */
 int VPIF_DISPLAY_MAX_DEVICES ; 
 int /*<<< orphan*/  free_vpif_objs () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 
 TYPE_2__ vpif_obj ; 

__attribute__((used)) static int vpif_remove(struct platform_device *device)
{
	struct channel_obj *ch;
	int i;

	if (vpif_obj.config->asd_sizes) {
		v4l2_async_notifier_unregister(&vpif_obj.notifier);
		v4l2_async_notifier_cleanup(&vpif_obj.notifier);
	}

	v4l2_device_unregister(&vpif_obj.v4l2_dev);

	kfree(vpif_obj.sd);
	/* un-register device */
	for (i = 0; i < VPIF_DISPLAY_MAX_DEVICES; i++) {
		/* Get the pointer to the channel object */
		ch = vpif_obj.dev[i];
		/* Unregister video device */
		video_unregister_device(&ch->video_dev);
	}
	free_vpif_objs();

	return 0;
}