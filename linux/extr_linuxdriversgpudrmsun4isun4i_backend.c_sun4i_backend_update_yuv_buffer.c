#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;
struct sun4i_backend {TYPE_1__ engine; } ;
struct drm_framebuffer {int* pitches; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_IYUVADD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_IYUVLINEWIDTH_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun4i_backend_update_yuv_buffer(struct sun4i_backend *backend,
					   struct drm_framebuffer *fb,
					   dma_addr_t paddr)
{
	/* TODO: Add support for the multi-planar YUV formats */
	DRM_DEBUG_DRIVER("Setting packed YUV buffer address to %pad\n", &paddr);
	regmap_write(backend->engine.regs, SUN4I_BACKEND_IYUVADD_REG(0), paddr);

	DRM_DEBUG_DRIVER("Layer line width: %d bits\n", fb->pitches[0] * 8);
	regmap_write(backend->engine.regs, SUN4I_BACKEND_IYUVLINEWIDTH_REG(0),
		     fb->pitches[0] * 8);

	return 0;
}