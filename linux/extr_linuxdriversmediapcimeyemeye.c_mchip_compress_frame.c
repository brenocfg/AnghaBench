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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MCHIP_HIC_CMD ; 
 int /*<<< orphan*/  MCHIP_HIC_CMD_START ; 
 int /*<<< orphan*/  MCHIP_HIC_MODE ; 
 int /*<<< orphan*/  MCHIP_HIC_MODE_STILL_COMP ; 
 int /*<<< orphan*/  MCHIP_HIC_STATUS ; 
 int /*<<< orphan*/  MCHIP_HIC_STATUS_IDLE ; 
 int MCHIP_MM_FIR_RDY ; 
 int mchip_comp_read_frame (int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mchip_delay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_free_frame () ; 
 int mchip_get_frame () ; 
 int /*<<< orphan*/  mchip_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_vrj_setup (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mchip_compress_frame(u8 *buf, int bufsize)
{
	u32 v;
	int len = -1, i;

	mchip_vrj_setup(0x3f);
	udelay(50);

	mchip_set(MCHIP_HIC_MODE, MCHIP_HIC_MODE_STILL_COMP);
	mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_START);

	mchip_delay(MCHIP_HIC_CMD, 0);
	for (i = 0; i < 100; ++i) {
		if (mchip_delay(MCHIP_HIC_STATUS, MCHIP_HIC_STATUS_IDLE))
			break;
		msleep(1);
	}

	for (i = 0; i < 4; ++i) {
		v = mchip_get_frame();
		if (v & MCHIP_MM_FIR_RDY) {
			len = mchip_comp_read_frame(v, buf, bufsize);
			break;
		}
		mchip_free_frame();
	}
	return len;
}