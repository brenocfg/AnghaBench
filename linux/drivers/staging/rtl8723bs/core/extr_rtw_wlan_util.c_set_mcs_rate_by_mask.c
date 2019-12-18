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

void set_mcs_rate_by_mask(u8 *mcs_set, u32 mask)
{
	u8 mcs_rate_1r = (u8)(mask&0xff);
	u8 mcs_rate_2r = (u8)((mask>>8)&0xff);
	u8 mcs_rate_3r = (u8)((mask>>16)&0xff);
	u8 mcs_rate_4r = (u8)((mask>>24)&0xff);

	mcs_set[0] &= mcs_rate_1r;
	mcs_set[1] &= mcs_rate_2r;
	mcs_set[2] &= mcs_rate_3r;
	mcs_set[3] &= mcs_rate_4r;
}