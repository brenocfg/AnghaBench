#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  cnt; } ;
struct TYPE_7__ {TYPE_2__ vsync; } ;
struct TYPE_8__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  cnt; } ;
struct TYPE_5__ {TYPE_4__ vsync; } ;
struct matrox_fb_info {TYPE_3__ crtc2; TYPE_1__ crtc1; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  M_ICLEAR ; 
 int /*<<< orphan*/  M_STATUS ; 
 int /*<<< orphan*/  matroxfb_crtc1_panpos (struct matrox_fb_info*) ; 
 int mga_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mga_outl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t matrox_irq(int irq, void *dev_id)
{
	u_int32_t status;
	int handled = 0;
	struct matrox_fb_info *minfo = dev_id;

	status = mga_inl(M_STATUS);

	if (status & 0x20) {
		mga_outl(M_ICLEAR, 0x20);
		minfo->crtc1.vsync.cnt++;
		matroxfb_crtc1_panpos(minfo);
		wake_up_interruptible(&minfo->crtc1.vsync.wait);
		handled = 1;
	}
	if (status & 0x200) {
		mga_outl(M_ICLEAR, 0x200);
		minfo->crtc2.vsync.cnt++;
		wake_up_interruptible(&minfo->crtc2.vsync.wait);
		handled = 1;
	}
	return IRQ_RETVAL(handled);
}