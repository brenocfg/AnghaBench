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
typedef  int u32 ;
struct vc4_crtc {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CRTC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PV_INTSTAT ; 
 int PV_INT_VFP_START ; 
 int /*<<< orphan*/  vc4_crtc_handle_vblank (struct vc4_crtc*) ; 

__attribute__((used)) static irqreturn_t vc4_crtc_irq_handler(int irq, void *data)
{
	struct vc4_crtc *vc4_crtc = data;
	u32 stat = CRTC_READ(PV_INTSTAT);
	irqreturn_t ret = IRQ_NONE;

	if (stat & PV_INT_VFP_START) {
		CRTC_WRITE(PV_INTSTAT, PV_INT_VFP_START);
		vc4_crtc_handle_vblank(vc4_crtc);
		ret = IRQ_HANDLED;
	}

	return ret;
}