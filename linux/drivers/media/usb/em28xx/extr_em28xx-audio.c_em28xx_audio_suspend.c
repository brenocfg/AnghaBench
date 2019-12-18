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
struct TYPE_4__ {int /*<<< orphan*/  stream_started; } ;
struct em28xx {scalar_t__ usb_audio_type; TYPE_2__ adev; TYPE_1__* intf; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ EM28XX_USB_AUDIO_VENDOR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  em28xx_deinit_isoc_audio (struct em28xx*) ; 

__attribute__((used)) static int em28xx_audio_suspend(struct em28xx *dev)
{
	if (!dev)
		return 0;

	if (dev->usb_audio_type != EM28XX_USB_AUDIO_VENDOR)
		return 0;

	dev_info(&dev->intf->dev, "Suspending audio extension\n");
	em28xx_deinit_isoc_audio(dev);
	atomic_set(&dev->adev.stream_started, 0);
	return 0;
}