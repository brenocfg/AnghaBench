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
struct drm_device {int /*<<< orphan*/  ctxlist; scalar_t__ dev_private; } ;
typedef  int /*<<< orphan*/  drm_via_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  via_cleanup_futex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  via_do_cleanup_map (struct drm_device*) ; 
 int /*<<< orphan*/  via_release_futex (int /*<<< orphan*/ *,int) ; 

int via_final_context(struct drm_device *dev, int context)
{
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;

	via_release_futex(dev_priv, context);

	/* Linux specific until context tracking code gets ported to BSD */
	/* Last context, perform cleanup */
	if (list_is_singular(&dev->ctxlist)) {
		DRM_DEBUG("Last Context\n");
		drm_irq_uninstall(dev);
		via_cleanup_futex(dev_priv);
		via_do_cleanup_map(dev);
	}
	return 1;
}