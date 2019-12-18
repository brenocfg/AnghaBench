#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ bit; unsigned int speed; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 TYPE_1__* settings ; 
 scalar_t__ test_bit (scalar_t__,unsigned long*) ; 

size_t phy_speeds(unsigned int *speeds, size_t size,
		  unsigned long *mask)
{
	size_t count;
	int i;

	for (i = 0, count = 0; i < ARRAY_SIZE(settings) && count < size; i++)
		if (settings[i].bit < __ETHTOOL_LINK_MODE_MASK_NBITS &&
		    test_bit(settings[i].bit, mask) &&
		    (count == 0 || speeds[count - 1] != settings[i].speed))
			speeds[count++] = settings[i].speed;

	return count;
}