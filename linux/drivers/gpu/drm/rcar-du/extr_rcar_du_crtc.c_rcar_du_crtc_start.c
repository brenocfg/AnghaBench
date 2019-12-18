#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ mode; } ;
struct rcar_du_crtc {int /*<<< orphan*/  group; TYPE_2__ crtc; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int DSYSR_SCM_INT_VIDEO ; 
 int DSYSR_SCM_MASK ; 
 int DSYSR_TVM_MASK ; 
 int DSYSR_TVM_MASTER ; 
 int /*<<< orphan*/  rcar_du_crtc_dsysr_clr_set (struct rcar_du_crtc*,int,int) ; 
 int /*<<< orphan*/  rcar_du_group_start_stop (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_du_crtc_start(struct rcar_du_crtc *rcrtc)
{
	bool interlaced;

	/*
	 * Select master sync mode. This enables display operation in master
	 * sync mode (with the HSYNC and VSYNC signals configured as outputs and
	 * actively driven).
	 */
	interlaced = rcrtc->crtc.mode.flags & DRM_MODE_FLAG_INTERLACE;
	rcar_du_crtc_dsysr_clr_set(rcrtc, DSYSR_TVM_MASK | DSYSR_SCM_MASK,
				   (interlaced ? DSYSR_SCM_INT_VIDEO : 0) |
				   DSYSR_TVM_MASTER);

	rcar_du_group_start_stop(rcrtc->group, true);
}