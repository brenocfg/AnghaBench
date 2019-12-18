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
struct brcms_phy {int dummy; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */

void
wlc_phy_get_pwrdet_offsets(struct brcms_phy *pi, s8 *cckoffset, s8 *ofdmoffset)
{
	*cckoffset = 0;
	*ofdmoffset = 0;
}