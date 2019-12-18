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
struct drm_vram_mm {int dummy; } ;
struct bochs_device {int /*<<< orphan*/  fb_size; int /*<<< orphan*/  fb_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct drm_vram_mm*) ; 
 int /*<<< orphan*/  drm_gem_vram_mm_funcs ; 
 struct drm_vram_mm* drm_vram_helper_alloc_mm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bochs_mm_init(struct bochs_device *bochs)
{
	struct drm_vram_mm *vmm;

	vmm = drm_vram_helper_alloc_mm(bochs->dev, bochs->fb_base,
				       bochs->fb_size,
				       &drm_gem_vram_mm_funcs);
	return PTR_ERR_OR_ZERO(vmm);
}