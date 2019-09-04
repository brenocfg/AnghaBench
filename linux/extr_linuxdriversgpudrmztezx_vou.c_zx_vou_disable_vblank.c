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
struct zx_vou_hw {scalar_t__ timing; } ;
struct zx_crtc {TYPE_1__* bits; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_frame_mask; } ;

/* Variables and functions */
 scalar_t__ TIMING_INT_CTRL ; 
 struct zx_vou_hw* crtc_to_vou (struct drm_crtc*) ; 
 struct zx_crtc* to_zx_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  zx_writel_mask (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zx_vou_disable_vblank(struct drm_crtc *crtc)
{
	struct zx_crtc *zcrtc = to_zx_crtc(crtc);
	struct zx_vou_hw *vou = crtc_to_vou(crtc);

	zx_writel_mask(vou->timing + TIMING_INT_CTRL,
		       zcrtc->bits->int_frame_mask, 0);
}