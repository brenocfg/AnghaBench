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
typedef  int uint8_t ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int NVReadVgaCrtc (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteVgaCrtc (struct drm_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NV_CIO_CRE_21 ; 

__attribute__((used)) static inline void
nv_lock_vga_crtc_shadow(struct drm_device *dev, int head, int lock)
{
	/* shadow lock: connects 0x60?3d? regs to "real" 0x3d? regs
	 * bit7: unlocks HDT, HBS, HBE, HRS, HRE, HEB
	 * bit6: seems to have some effect on CR09 (double scan, VBS_9)
	 * bit5: unlocks HDE
	 * bit4: unlocks VDE
	 * bit3: unlocks VDT, OVL, VRS, ?VRE?, VBS, VBE, LSR, EBR
	 * bit2: same as bit 1 of 0x60?804
	 * bit0: same as bit 0 of 0x60?804
	 */

	uint8_t cr21 = lock;

	if (lock < 0)
		/* 0xfa is generic "unlock all" mask */
		cr21 = NVReadVgaCrtc(dev, head, NV_CIO_CRE_21) | 0xfa;

	NVWriteVgaCrtc(dev, head, NV_CIO_CRE_21, cr21);
}