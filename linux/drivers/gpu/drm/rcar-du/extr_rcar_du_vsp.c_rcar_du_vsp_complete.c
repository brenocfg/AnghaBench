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
struct rcar_du_crtc {int /*<<< orphan*/  crtc; scalar_t__ vblank_enable; } ;

/* Variables and functions */
 unsigned int VSP1_DU_STATUS_COMPLETE ; 
 unsigned int VSP1_DU_STATUS_WRITEBACK ; 
 int /*<<< orphan*/  drm_crtc_add_crc_entry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcar_du_crtc_finish_page_flip (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  rcar_du_writeback_complete (struct rcar_du_crtc*) ; 

__attribute__((used)) static void rcar_du_vsp_complete(void *private, unsigned int status, u32 crc)
{
	struct rcar_du_crtc *crtc = private;

	if (crtc->vblank_enable)
		drm_crtc_handle_vblank(&crtc->crtc);

	if (status & VSP1_DU_STATUS_COMPLETE)
		rcar_du_crtc_finish_page_flip(crtc);
	if (status & VSP1_DU_STATUS_WRITEBACK)
		rcar_du_writeback_complete(crtc);

	drm_crtc_add_crc_entry(&crtc->crtc, false, 0, &crc);
}