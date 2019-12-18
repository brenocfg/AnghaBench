#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* dev; } ;
struct intel_fbdev {TYPE_1__* fb; TYPE_3__ helper; int /*<<< orphan*/  vma_flags; scalar_t__ vma; } ;
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (TYPE_3__*) ; 
 int /*<<< orphan*/  drm_framebuffer_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_unpin_fb_vma (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct intel_fbdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_fbdev_destroy(struct intel_fbdev *ifbdev)
{
	/* We rely on the object-free to release the VMA pinning for
	 * the info->screen_base mmaping. Leaking the VMA is simpler than
	 * trying to rectify all the possible error paths leading here.
	 */

	drm_fb_helper_fini(&ifbdev->helper);

	if (ifbdev->vma) {
		mutex_lock(&ifbdev->helper.dev->struct_mutex);
		intel_unpin_fb_vma(ifbdev->vma, ifbdev->vma_flags);
		mutex_unlock(&ifbdev->helper.dev->struct_mutex);
	}

	if (ifbdev->fb)
		drm_framebuffer_remove(&ifbdev->fb->base);

	kfree(ifbdev);
}