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
typedef  int u32 ;
struct ltdc_device {int /*<<< orphan*/  regs; } ;
struct drm_crtc {TYPE_2__* state; } ;
struct drm_color_lut {int red; int green; int blue; } ;
struct TYPE_4__ {TYPE_1__* gamma_lut; int /*<<< orphan*/  color_mgmt_changed; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int CLUT_SIZE ; 
 int /*<<< orphan*/  LTDC_L1CLUTWR ; 
 struct ltdc_device* crtc_to_ltdc (struct drm_crtc*) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ltdc_crtc_update_clut(struct drm_crtc *crtc)
{
	struct ltdc_device *ldev = crtc_to_ltdc(crtc);
	struct drm_color_lut *lut;
	u32 val;
	int i;

	if (!crtc->state->color_mgmt_changed || !crtc->state->gamma_lut)
		return;

	lut = (struct drm_color_lut *)crtc->state->gamma_lut->data;

	for (i = 0; i < CLUT_SIZE; i++, lut++) {
		val = ((lut->red << 8) & 0xff0000) | (lut->green & 0xff00) |
			(lut->blue >> 8) | (i << 24);
		reg_write(ldev->regs, LTDC_L1CLUTWR, val);
	}
}