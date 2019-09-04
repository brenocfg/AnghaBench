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
struct drm_gem_object {int dummy; } ;

/* Variables and functions */

int omap_gem_put_pages(struct drm_gem_object *obj)
{
	/* do something here if we dynamically attach/detach pages.. at
	 * least they would no longer need to be pinned if everyone has
	 * released the pages..
	 */
	return 0;
}