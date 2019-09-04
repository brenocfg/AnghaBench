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
struct exynos_drm_plane {unsigned int index; } ;
struct exynos_drm_crtc {struct decon_context* ctx; } ;
struct decon_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECON_WINCONx (unsigned int) ; 
 int /*<<< orphan*/  WINCONx_ENWIN_F ; 
 int /*<<< orphan*/  decon_set_bits (struct decon_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decon_disable_plane(struct exynos_drm_crtc *crtc,
				struct exynos_drm_plane *plane)
{
	struct decon_context *ctx = crtc->ctx;
	unsigned int win = plane->index;

	decon_set_bits(ctx, DECON_WINCONx(win), WINCONx_ENWIN_F, 0);
}