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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int b43_radio_read (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool b43_radio_wait_value(struct b43_wldev *dev, u16 offset, u16 mask,
			  u16 value, int delay, int timeout)
{
	u16 val;
	int i;

	for (i = 0; i < timeout; i += delay) {
		val = b43_radio_read(dev, offset);
		if ((val & mask) == value)
			return true;
		udelay(delay);
	}
	return false;
}