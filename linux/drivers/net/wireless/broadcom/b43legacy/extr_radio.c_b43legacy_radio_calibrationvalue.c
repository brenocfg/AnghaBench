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
typedef  int u16 ;
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int* rcc_table ; 

u16 b43legacy_radio_calibrationvalue(struct b43legacy_wldev *dev)
{
	u16 reg;
	u16 index;
	u16 ret;

	reg = b43legacy_radio_read16(dev, 0x0060);
	index = (reg & 0x001E) >> 1;
	ret = rcc_table[index] << 1;
	ret |= (reg & 0x0001);
	ret |= 0x0020;

	return ret;
}