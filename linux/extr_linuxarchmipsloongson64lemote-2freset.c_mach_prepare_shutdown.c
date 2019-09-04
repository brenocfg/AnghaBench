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

/* Variables and functions */
#define  MACH_LEMOTE_FL2F 132 
#define  MACH_LEMOTE_LL2F 131 
#define  MACH_LEMOTE_ML2F7 130 
#define  MACH_LEMOTE_NAS 129 
#define  MACH_LEMOTE_YL2F89 128 
 int /*<<< orphan*/  fl2f_shutdown () ; 
 int mips_machtype ; 
 int /*<<< orphan*/  ml2f_shutdown () ; 
 int /*<<< orphan*/  yl2f89_shutdown () ; 

void mach_prepare_shutdown(void)
{
	switch (mips_machtype) {
	case MACH_LEMOTE_FL2F:
	case MACH_LEMOTE_NAS:
	case MACH_LEMOTE_LL2F:
		fl2f_shutdown();
		break;
	case MACH_LEMOTE_ML2F7:
		ml2f_shutdown();
		break;
	case MACH_LEMOTE_YL2F89:
		yl2f89_shutdown();
		break;
	default:
		break;
	}
}