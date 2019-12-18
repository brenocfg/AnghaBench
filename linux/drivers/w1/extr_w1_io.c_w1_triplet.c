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
struct w1_master {TYPE_1__* bus_master; } ;
struct TYPE_2__ {int (* triplet ) (int /*<<< orphan*/ ,int) ;scalar_t__ touch_bit; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int w1_touch_bit (struct w1_master*,int) ; 
 int /*<<< orphan*/  w1_write_bit (struct w1_master*,int) ; 

u8 w1_triplet(struct w1_master *dev, int bdir)
{
	if (dev->bus_master->triplet)
		return dev->bus_master->triplet(dev->bus_master->data, bdir);
	else {
		u8 id_bit   = w1_touch_bit(dev, 1);
		u8 comp_bit = w1_touch_bit(dev, 1);
		u8 retval;

		if (id_bit && comp_bit)
			return 0x03;  /* error */

		if (!id_bit && !comp_bit) {
			/* Both bits are valid, take the direction given */
			retval = bdir ? 0x04 : 0;
		} else {
			/* Only one bit is valid, take that direction */
			bdir = id_bit;
			retval = id_bit ? 0x05 : 0x02;
		}

		if (dev->bus_master->touch_bit)
			w1_touch_bit(dev, bdir);
		else
			w1_write_bit(dev, bdir);
		return retval;
	}
}