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
struct pm2fb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM2F_APERTURE_BYTESWAP ; 
 int /*<<< orphan*/  PM2F_APERTURE_HALFWORDSWAP ; 
 int /*<<< orphan*/  PM2F_APERTURE_STANDARD ; 
 int /*<<< orphan*/  PM2R_APERTURE_ONE ; 
 int /*<<< orphan*/  PM2R_APERTURE_TWO ; 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_aperture(struct pm2fb_par *p, u32 depth)
{
	/*
	 * The hardware is little-endian. When used in big-endian
	 * hosts, the on-chip aperture settings are used where
	 * possible to translate from host to card byte order.
	 */
	WAIT_FIFO(p, 2);
#ifdef __LITTLE_ENDIAN
	pm2_WR(p, PM2R_APERTURE_ONE, PM2F_APERTURE_STANDARD);
#else
	switch (depth) {
	case 24:	/* RGB->BGR */
		/*
		 * We can't use the aperture to translate host to
		 * card byte order here, so we switch to BGR mode
		 * in pm2fb_set_par().
		 */
	case 8:		/* B->B */
		pm2_WR(p, PM2R_APERTURE_ONE, PM2F_APERTURE_STANDARD);
		break;
	case 16:	/* HL->LH */
		pm2_WR(p, PM2R_APERTURE_ONE, PM2F_APERTURE_HALFWORDSWAP);
		break;
	case 32:	/* RGBA->ABGR */
		pm2_WR(p, PM2R_APERTURE_ONE, PM2F_APERTURE_BYTESWAP);
		break;
	}
#endif

	/* We don't use aperture two, so this may be superflous */
	pm2_WR(p, PM2R_APERTURE_TWO, PM2F_APERTURE_STANDARD);
}