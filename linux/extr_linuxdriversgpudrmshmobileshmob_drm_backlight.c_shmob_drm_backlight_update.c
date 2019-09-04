#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct shmob_drm_device {TYPE_3__* pdata; } ;
struct TYPE_6__ {TYPE_1__* dev; } ;
struct shmob_drm_connector {TYPE_2__ connector; } ;
struct shmob_drm_backlight_data {int (* set_brightness ) (int) ;} ;
struct TYPE_8__ {int brightness; scalar_t__ power; int state; } ;
struct backlight_device {TYPE_4__ props; } ;
struct TYPE_7__ {struct shmob_drm_backlight_data backlight; } ;
struct TYPE_5__ {struct shmob_drm_device* dev_private; } ;

/* Variables and functions */
 int BL_CORE_SUSPENDED ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 struct shmob_drm_connector* bl_get_data (struct backlight_device*) ; 
 int stub1 (int) ; 

__attribute__((used)) static int shmob_drm_backlight_update(struct backlight_device *bdev)
{
	struct shmob_drm_connector *scon = bl_get_data(bdev);
	struct shmob_drm_device *sdev = scon->connector.dev->dev_private;
	const struct shmob_drm_backlight_data *bdata = &sdev->pdata->backlight;
	int brightness = bdev->props.brightness;

	if (bdev->props.power != FB_BLANK_UNBLANK ||
	    bdev->props.state & BL_CORE_SUSPENDED)
		brightness = 0;

	return bdata->set_brightness(brightness);
}