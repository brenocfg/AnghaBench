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
struct exynos_drm_ipp_funcs {int dummy; } ;
struct exynos_drm_ipp_formats {int dummy; } ;
struct exynos_drm_ipp {unsigned int capabilities; char const* name; unsigned int num_formats; scalar_t__ id; int /*<<< orphan*/  head; struct exynos_drm_ipp_formats const* formats; struct exynos_drm_ipp_funcs const* funcs; struct device* dev; int /*<<< orphan*/  done_wq; int /*<<< orphan*/  todo_list; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipp_list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_ipp ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int exynos_drm_ipp_register(struct device *dev, struct exynos_drm_ipp *ipp,
		const struct exynos_drm_ipp_funcs *funcs, unsigned int caps,
		const struct exynos_drm_ipp_formats *formats,
		unsigned int num_formats, const char *name)
{
	WARN_ON(!ipp);
	WARN_ON(!funcs);
	WARN_ON(!formats);
	WARN_ON(!num_formats);

	spin_lock_init(&ipp->lock);
	INIT_LIST_HEAD(&ipp->todo_list);
	init_waitqueue_head(&ipp->done_wq);
	ipp->dev = dev;
	ipp->funcs = funcs;
	ipp->capabilities = caps;
	ipp->name = name;
	ipp->formats = formats;
	ipp->num_formats = num_formats;

	/* ipp_list modification is serialized by component framework */
	list_add_tail(&ipp->head, &ipp_list);
	ipp->id = num_ipp++;

	DRM_DEV_DEBUG_DRIVER(dev, "Registered ipp %d\n", ipp->id);

	return 0;
}