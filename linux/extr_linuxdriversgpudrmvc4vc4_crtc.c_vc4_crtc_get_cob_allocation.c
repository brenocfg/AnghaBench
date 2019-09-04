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
typedef  int u32 ;
struct vc4_dev {int dummy; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct vc4_crtc {int cob_size; int /*<<< orphan*/  channel; TYPE_1__ base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int HVS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCALER_DISPBASEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCALER_DISPBASEX_BASE ; 
 int /*<<< orphan*/  SCALER_DISPBASEX_TOP ; 
 int VC4_GET_FIELD (int,int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static void
vc4_crtc_get_cob_allocation(struct vc4_crtc *vc4_crtc)
{
	struct drm_device *drm = vc4_crtc->base.dev;
	struct vc4_dev *vc4 = to_vc4_dev(drm);
	u32 dispbase = HVS_READ(SCALER_DISPBASEX(vc4_crtc->channel));
	/* Top/base are supposed to be 4-pixel aligned, but the
	 * Raspberry Pi firmware fills the low bits (which are
	 * presumably ignored).
	 */
	u32 top = VC4_GET_FIELD(dispbase, SCALER_DISPBASEX_TOP) & ~3;
	u32 base = VC4_GET_FIELD(dispbase, SCALER_DISPBASEX_BASE) & ~3;

	vc4_crtc->cob_size = top - base + 4;
}