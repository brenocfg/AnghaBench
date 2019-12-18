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
struct TYPE_3__ {scalar_t__ accelerator; } ;
struct matrox_fb_info {TYPE_2__* pcidev; TYPE_1__ devflags; int /*<<< orphan*/  irq_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ FB_ACCEL_MATROX_MGAG400 ; 
 int /*<<< orphan*/  M_IEN ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct matrox_fb_info*) ; 
 int /*<<< orphan*/  matroxfb_crtc1_panpos (struct matrox_fb_info*) ; 
 int mga_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mga_outl (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void matroxfb_disable_irq(struct matrox_fb_info *minfo)
{
	if (test_and_clear_bit(0, &minfo->irq_flags)) {
		/* Flush pending pan-at-vbl request... */
		matroxfb_crtc1_panpos(minfo);
		if (minfo->devflags.accelerator == FB_ACCEL_MATROX_MGAG400)
			mga_outl(M_IEN, mga_inl(M_IEN) & ~0x220);
		else
			mga_outl(M_IEN, mga_inl(M_IEN) & ~0x20);
		free_irq(minfo->pcidev->irq, minfo);
	}
}