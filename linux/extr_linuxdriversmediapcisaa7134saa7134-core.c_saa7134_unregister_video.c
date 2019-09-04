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
struct saa7134_dev {int /*<<< orphan*/ * radio_dev; int /*<<< orphan*/ * vbi_dev; int /*<<< orphan*/ * video_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa7134_media_release (struct saa7134_dev*) ; 
 int /*<<< orphan*/  video_device_release (int /*<<< orphan*/ *) ; 
 scalar_t__ video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void saa7134_unregister_video(struct saa7134_dev *dev)
{
	saa7134_media_release(dev);

	if (dev->video_dev) {
		if (video_is_registered(dev->video_dev))
			video_unregister_device(dev->video_dev);
		else
			video_device_release(dev->video_dev);
		dev->video_dev = NULL;
	}
	if (dev->vbi_dev) {
		if (video_is_registered(dev->vbi_dev))
			video_unregister_device(dev->vbi_dev);
		else
			video_device_release(dev->vbi_dev);
		dev->vbi_dev = NULL;
	}
	if (dev->radio_dev) {
		if (video_is_registered(dev->radio_dev))
			video_unregister_device(dev->radio_dev);
		else
			video_device_release(dev->radio_dev);
		dev->radio_dev = NULL;
	}
}