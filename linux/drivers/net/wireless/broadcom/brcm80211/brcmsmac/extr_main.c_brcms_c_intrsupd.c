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
struct brcms_c_info {int macintstatus; } ;

/* Variables and functions */
 int wlc_intstatus (struct brcms_c_info*,int) ; 

bool brcms_c_intrsupd(struct brcms_c_info *wlc)
{
	u32 macintstatus;

	/* read and clear macintstatus and intstatus registers */
	macintstatus = wlc_intstatus(wlc, false);

	/* device is removed */
	if (macintstatus == 0xffffffff)
		return false;

	/* update interrupt status in software */
	wlc->macintstatus |= macintstatus;

	return true;
}