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
typedef  int /*<<< orphan*/  u8 ;
struct malidp_drm {int /*<<< orphan*/  dev; } ;
struct drm_mode_create_dumb {int width; int bpp; int /*<<< orphan*/  pitch; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct malidp_drm* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int drm_gem_cma_dumb_create_internal (struct drm_file*,struct drm_device*,struct drm_mode_create_dumb*) ; 
 int /*<<< orphan*/  malidp_hw_get_pitch_align (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int malidp_dumb_create(struct drm_file *file_priv,
			      struct drm_device *drm,
			      struct drm_mode_create_dumb *args)
{
	struct malidp_drm *malidp = drm->dev_private;
	/* allocate for the worst case scenario, i.e. rotated buffers */
	u8 alignment = malidp_hw_get_pitch_align(malidp->dev, 1);

	args->pitch = ALIGN(DIV_ROUND_UP(args->width * args->bpp, 8), alignment);

	return drm_gem_cma_dumb_create_internal(file_priv, drm, args);
}