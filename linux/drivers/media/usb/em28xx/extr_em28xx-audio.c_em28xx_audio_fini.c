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
struct TYPE_4__ {int /*<<< orphan*/ * sndcard; int /*<<< orphan*/  wq_trigger; } ;
struct em28xx {scalar_t__ usb_audio_type; int /*<<< orphan*/  ref; TYPE_2__ adev; TYPE_1__* intf; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ EM28XX_USB_AUDIO_VENDOR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  em28xx_audio_free_urb (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_free_device ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em28xx_audio_fini(struct em28xx *dev)
{
	if (!dev)
		return 0;

	if (dev->usb_audio_type != EM28XX_USB_AUDIO_VENDOR) {
		/*
		 * This device does not support the extension (in this case
		 * the device is expecting the snd-usb-audio module or
		 * doesn't have analog audio support at all)
		 */
		return 0;
	}

	dev_info(&dev->intf->dev, "Closing audio extension\n");

	if (dev->adev.sndcard) {
		snd_card_disconnect(dev->adev.sndcard);
		flush_work(&dev->adev.wq_trigger);

		em28xx_audio_free_urb(dev);

		snd_card_free(dev->adev.sndcard);
		dev->adev.sndcard = NULL;
	}

	kref_put(&dev->ref, em28xx_free_device);
	return 0;
}