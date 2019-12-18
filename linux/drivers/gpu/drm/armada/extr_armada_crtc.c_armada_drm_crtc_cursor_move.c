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
struct drm_crtc {int dummy; } ;
struct armada_crtc {int cursor_x; int cursor_y; TYPE_1__* variant; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_spu_adv_reg; } ;

/* Variables and functions */
 int EFAULT ; 
 int armada_drm_crtc_cursor_update (struct armada_crtc*,int) ; 
 struct armada_crtc* drm_to_armada_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int armada_drm_crtc_cursor_move(struct drm_crtc *crtc, int x, int y)
{
	struct armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	int ret;

	/* If no cursor support, replicate drm's return value */
	if (!dcrtc->variant->has_spu_adv_reg)
		return -EFAULT;

	dcrtc->cursor_x = x;
	dcrtc->cursor_y = y;
	ret = armada_drm_crtc_cursor_update(dcrtc, false);

	return ret;
}