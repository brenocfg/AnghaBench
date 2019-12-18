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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_fini (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct drm_device*) ; 
 int /*<<< orphan*/  udl_fini (struct drm_device*) ; 
 int /*<<< orphan*/  udl_modeset_cleanup (struct drm_device*) ; 

__attribute__((used)) static void udl_driver_release(struct drm_device *dev)
{
	udl_fini(dev);
	udl_modeset_cleanup(dev);
	drm_dev_fini(dev);
	kfree(dev);
}