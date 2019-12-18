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
struct rcar_du_device {struct drm_device* ddev; } ;
struct platform_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 struct rcar_du_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int rcar_du_remove(struct platform_device *pdev)
{
	struct rcar_du_device *rcdu = platform_get_drvdata(pdev);
	struct drm_device *ddev = rcdu->ddev;

	drm_dev_unregister(ddev);

	drm_kms_helper_poll_fini(ddev);
	drm_mode_config_cleanup(ddev);

	drm_dev_put(ddev);

	return 0;
}