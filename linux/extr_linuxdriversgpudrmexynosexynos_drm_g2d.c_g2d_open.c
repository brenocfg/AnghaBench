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
struct drm_file {struct drm_exynos_file_private* driver_priv; } ;
struct drm_exynos_file_private {int /*<<< orphan*/  userptr_list; int /*<<< orphan*/  event_list; int /*<<< orphan*/  inuse_cmdlist; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

int g2d_open(struct drm_device *drm_dev, struct drm_file *file)
{
	struct drm_exynos_file_private *file_priv = file->driver_priv;

	INIT_LIST_HEAD(&file_priv->inuse_cmdlist);
	INIT_LIST_HEAD(&file_priv->event_list);
	INIT_LIST_HEAD(&file_priv->userptr_list);

	return 0;
}