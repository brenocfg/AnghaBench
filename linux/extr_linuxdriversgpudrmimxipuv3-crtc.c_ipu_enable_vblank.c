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
struct ipu_crtc {int /*<<< orphan*/  irq; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct ipu_crtc* to_ipu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int ipu_enable_vblank(struct drm_crtc *crtc)
{
	struct ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);

	enable_irq(ipu_crtc->irq);

	return 0;
}