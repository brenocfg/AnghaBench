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
struct gm12u320_device {int dummy; } ;
struct drm_device {struct gm12u320_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  gm12u320_usb_free (struct gm12u320_device*) ; 
 int /*<<< orphan*/  kfree (struct gm12u320_device*) ; 

__attribute__((used)) static void gm12u320_driver_release(struct drm_device *dev)
{
	struct gm12u320_device *gm12u320 = dev->dev_private;

	gm12u320_usb_free(gm12u320);
	drm_mode_config_cleanup(dev);
	drm_dev_fini(dev);
	kfree(gm12u320);
}