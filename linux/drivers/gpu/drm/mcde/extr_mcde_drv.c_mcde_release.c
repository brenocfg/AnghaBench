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
struct mcde {int dummy; } ;
struct drm_device {struct mcde* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct mcde*) ; 

__attribute__((used)) static void mcde_release(struct drm_device *drm)
{
	struct mcde *mcde = drm->dev_private;

	drm_mode_config_cleanup(drm);
	drm_dev_fini(drm);
	kfree(mcde);
}