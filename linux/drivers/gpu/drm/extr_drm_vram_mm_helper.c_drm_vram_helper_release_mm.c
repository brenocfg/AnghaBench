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
struct drm_device {int /*<<< orphan*/ * vram_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_vram_mm_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void drm_vram_helper_release_mm(struct drm_device *dev)
{
	if (!dev->vram_mm)
		return;

	drm_vram_mm_cleanup(dev->vram_mm);
	kfree(dev->vram_mm);
	dev->vram_mm = NULL;
}