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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gma_crtc_load_lut (struct drm_crtc*) ; 

int gma_crtc_gamma_set(struct drm_crtc *crtc, u16 *red, u16 *green, u16 *blue,
		       u32 size,
		       struct drm_modeset_acquire_ctx *ctx)
{
	gma_crtc_load_lut(crtc);

	return 0;
}