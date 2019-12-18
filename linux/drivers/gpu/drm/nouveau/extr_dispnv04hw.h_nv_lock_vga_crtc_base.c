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
 int /*<<< orphan*/  NV_CIO_CR_VRE_INDEX ; 

__attribute__((used)) static inline bool
nv_lock_vga_crtc_base(struct drm_device *dev, int head, bool lock)
{
	uint8_t cr11 = NVReadVgaCrtc(dev, head, NV_CIO_CR_VRE_INDEX);
	bool waslocked = cr11 & 0x80;

	if (lock)
		cr11 |= 0x80;
	else
		cr11 &= ~0x80;
	NVWriteVgaCrtc(dev, head, NV_CIO_CR_VRE_INDEX, cr11);

	return waslocked;
}