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
struct shmob_drm_plane {scalar_t__* dma; TYPE_1__* format; } ;
struct drm_gem_cma_object {scalar_t__ paddr; } ;
struct drm_framebuffer {int* pitches; scalar_t__* offsets; } ;
struct TYPE_2__ {int bpp; scalar_t__ yuv; } ;

/* Variables and functions */
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int) ; 

__attribute__((used)) static void shmob_drm_plane_compute_base(struct shmob_drm_plane *splane,
					 struct drm_framebuffer *fb,
					 int x, int y)
{
	struct drm_gem_cma_object *gem;
	unsigned int bpp;

	bpp = splane->format->yuv ? 8 : splane->format->bpp;
	gem = drm_fb_cma_get_gem_obj(fb, 0);
	splane->dma[0] = gem->paddr + fb->offsets[0]
		       + y * fb->pitches[0] + x * bpp / 8;

	if (splane->format->yuv) {
		bpp = splane->format->bpp - 8;
		gem = drm_fb_cma_get_gem_obj(fb, 1);
		splane->dma[1] = gem->paddr + fb->offsets[1]
			       + y / (bpp == 4 ? 2 : 1) * fb->pitches[1]
			       + x * (bpp == 16 ? 2 : 1);
	}
}