#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int chipset; } ;
typedef  TYPE_1__ drm_mga_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
#define  MGA_CARD_TYPE_G200 130 
#define  MGA_CARD_TYPE_G400 129 
#define  MGA_CARD_TYPE_G550 128 
 scalar_t__ MGA_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGA_WACCEPTSEQ ; 
 int MGA_WCACHEFLUSH_ENABLE ; 
 int /*<<< orphan*/  MGA_WGETMSB ; 
 int /*<<< orphan*/  MGA_WIADDR ; 
 int /*<<< orphan*/  MGA_WIADDR2 ; 
 int MGA_WMASTER_ENABLE ; 
 int /*<<< orphan*/  MGA_WMISC ; 
 int MGA_WMODE_SUSPEND ; 
 int /*<<< orphan*/  MGA_WRITE (int /*<<< orphan*/ ,int) ; 
 int MGA_WUCODECACHE_ENABLE ; 
 int /*<<< orphan*/  MGA_WVRTXSZ ; 
 scalar_t__ WMISC_EXPECTED ; 

int mga_warp_init(drm_mga_private_t *dev_priv)
{
	u32 wmisc;

	/* FIXME: Get rid of these damned magic numbers...
	 */
	switch (dev_priv->chipset) {
	case MGA_CARD_TYPE_G400:
	case MGA_CARD_TYPE_G550:
		MGA_WRITE(MGA_WIADDR2, MGA_WMODE_SUSPEND);
		MGA_WRITE(MGA_WGETMSB, 0x00000E00);
		MGA_WRITE(MGA_WVRTXSZ, 0x00001807);
		MGA_WRITE(MGA_WACCEPTSEQ, 0x18000000);
		break;
	case MGA_CARD_TYPE_G200:
		MGA_WRITE(MGA_WIADDR, MGA_WMODE_SUSPEND);
		MGA_WRITE(MGA_WGETMSB, 0x1606);
		MGA_WRITE(MGA_WVRTXSZ, 7);
		break;
	default:
		return -EINVAL;
	}

	MGA_WRITE(MGA_WMISC, (MGA_WUCODECACHE_ENABLE |
			      MGA_WMASTER_ENABLE | MGA_WCACHEFLUSH_ENABLE));
	wmisc = MGA_READ(MGA_WMISC);
	if (wmisc != WMISC_EXPECTED) {
		DRM_ERROR("WARP engine config failed! 0x%x != 0x%x\n",
			  wmisc, WMISC_EXPECTED);
		return -EINVAL;
	}

	return 0;
}