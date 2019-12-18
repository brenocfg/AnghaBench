#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct malidp_hw_device {TYPE_3__* hw; } ;
struct malidp_drm {struct malidp_hw_device* dev; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vsync_irq; } ;
struct TYPE_5__ {TYPE_1__ de_irq_map; } ;
struct TYPE_6__ {TYPE_2__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALIDP_DE_BLOCK ; 
 struct malidp_drm* crtc_to_malidp_device (struct drm_crtc*) ; 
 int /*<<< orphan*/  malidp_hw_disable_irq (struct malidp_hw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void malidp_crtc_disable_vblank(struct drm_crtc *crtc)
{
	struct malidp_drm *malidp = crtc_to_malidp_device(crtc);
	struct malidp_hw_device *hwdev = malidp->dev;

	malidp_hw_disable_irq(hwdev, MALIDP_DE_BLOCK,
			      hwdev->hw->map.de_irq_map.vsync_irq);
}