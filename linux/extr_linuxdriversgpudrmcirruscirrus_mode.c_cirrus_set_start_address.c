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
struct drm_crtc {TYPE_1__* dev; } ;
struct cirrus_device {int dummy; } ;
struct TYPE_2__ {struct cirrus_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_DATA ; 
 int /*<<< orphan*/  CRT_INDEX ; 
 int RREG8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG_CRT (int,int) ; 

__attribute__((used)) static void cirrus_set_start_address(struct drm_crtc *crtc, unsigned offset)
{
	struct cirrus_device *cdev = crtc->dev->dev_private;
	u32 addr;
	u8 tmp;

	addr = offset >> 2;
	WREG_CRT(0x0c, (u8)((addr >> 8) & 0xff));
	WREG_CRT(0x0d, (u8)(addr & 0xff));

	WREG8(CRT_INDEX, 0x1b);
	tmp = RREG8(CRT_DATA);
	tmp &= 0xf2;
	tmp |= (addr >> 16) & 0x01;
	tmp |= (addr >> 15) & 0x0c;
	WREG_CRT(0x1b, tmp);
	WREG8(CRT_INDEX, 0x1d);
	tmp = RREG8(CRT_DATA);
	tmp &= 0x7f;
	tmp |= (addr >> 12) & 0x80;
	WREG_CRT(0x1d, tmp);
}