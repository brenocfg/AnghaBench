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
typedef  int u8 ;
typedef  int u32 ;
struct mga_device {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct mga_device* dev_private; } ;

/* Variables and functions */
 int MGAREG_CRTCEXT_DATA ; 
 int /*<<< orphan*/  MGAREG_CRTCEXT_INDEX ; 
 int MGAREG_VCOUNT ; 
 int RREG8 (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG_CRT (int,int) ; 
 int /*<<< orphan*/  WREG_ECRT (int,int) ; 

__attribute__((used)) static void mga_set_start_address(struct drm_crtc *crtc, unsigned offset)
{
	struct mga_device *mdev = crtc->dev->dev_private;
	u32 addr;
	int count;
	u8 crtcext0;

	while (RREG8(0x1fda) & 0x08);
	while (!(RREG8(0x1fda) & 0x08));

	count = RREG8(MGAREG_VCOUNT) + 2;
	while (RREG8(MGAREG_VCOUNT) < count);

	WREG8(MGAREG_CRTCEXT_INDEX, 0);
	crtcext0 = RREG8(MGAREG_CRTCEXT_DATA);
	crtcext0 &= 0xB0;
	addr = offset / 8;
	/* Can't store addresses any higher than that...
	   but we also don't have more than 16MB of memory, so it should be fine. */
	WARN_ON(addr > 0x1fffff);
	crtcext0 |= (!!(addr & (1<<20)))<<6;
	WREG_CRT(0x0d, (u8)(addr & 0xff));
	WREG_CRT(0x0c, (u8)(addr >> 8) & 0xff);
	WREG_ECRT(0x0, ((u8)(addr >> 16) & 0xf) | crtcext0);
}