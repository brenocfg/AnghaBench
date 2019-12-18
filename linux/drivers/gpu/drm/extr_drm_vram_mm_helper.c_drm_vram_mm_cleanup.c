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
struct drm_vram_mm {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 

void drm_vram_mm_cleanup(struct drm_vram_mm *vmm)
{
	ttm_bo_device_release(&vmm->bdev);
}