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
struct rcar_du_device {int dummy; } ;
struct drm_mode_create_dumb {int width; int bpp; int /*<<< orphan*/  pitch; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct rcar_du_device* dev_private; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  RCAR_DU_QUIRK_ALIGN_128B ; 
 int drm_gem_cma_dumb_create_internal (struct drm_file*,struct drm_device*,struct drm_mode_create_dumb*) ; 
 scalar_t__ rcar_du_needs (struct rcar_du_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup (unsigned int,unsigned int) ; 

int rcar_du_dumb_create(struct drm_file *file, struct drm_device *dev,
			struct drm_mode_create_dumb *args)
{
	struct rcar_du_device *rcdu = dev->dev_private;
	unsigned int min_pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	unsigned int align;

	/*
	 * The R8A7779 DU requires a 16 pixels pitch alignment as documented,
	 * but the R8A7790 DU seems to require a 128 bytes pitch alignment.
	 */
	if (rcar_du_needs(rcdu, RCAR_DU_QUIRK_ALIGN_128B))
		align = 128;
	else
		align = 16 * args->bpp / 8;

	args->pitch = roundup(min_pitch, align);

	return drm_gem_cma_dumb_create_internal(file, dev, args);
}