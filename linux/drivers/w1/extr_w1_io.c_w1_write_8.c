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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* write_byte ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w1_post_write (struct w1_master*) ; 
 int /*<<< orphan*/  w1_pre_write (struct w1_master*) ; 
 int /*<<< orphan*/  w1_touch_bit (struct w1_master*,int) ; 

void w1_write_8(struct w1_master *dev, u8 byte)
{
	int i;

	if (dev->bus_master->write_byte) {
		w1_pre_write(dev);
		dev->bus_master->write_byte(dev->bus_master->data, byte);
	}
	else
		for (i = 0; i < 8; ++i) {
			if (i == 7)
				w1_pre_write(dev);
			w1_touch_bit(dev, (byte >> i) & 0x1);
		}
	w1_post_write(dev);
}