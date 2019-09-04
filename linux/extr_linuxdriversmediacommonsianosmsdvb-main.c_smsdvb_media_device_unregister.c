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
struct smsdvb_client_t {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void smsdvb_media_device_unregister(struct smsdvb_client_t *client)
{
#ifdef CONFIG_MEDIA_CONTROLLER_DVB
	struct smscore_device_t *coredev = client->coredev;

	if (!coredev->media_dev)
		return;
	media_device_unregister(coredev->media_dev);
	media_device_cleanup(coredev->media_dev);
	kfree(coredev->media_dev);
	coredev->media_dev = NULL;
#endif
}