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
struct shmob_drm_connector {TYPE_2__* backlight; } ;
struct TYPE_3__ {int /*<<< orphan*/  power; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  backlight_update_status (TYPE_2__*) ; 

void shmob_drm_backlight_dpms(struct shmob_drm_connector *scon, int mode)
{
	if (scon->backlight == NULL)
		return;

	scon->backlight->props.power = mode == DRM_MODE_DPMS_ON
				     ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
	backlight_update_status(scon->backlight);
}