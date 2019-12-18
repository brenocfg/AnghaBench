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
struct TYPE_2__ {int (* read_block ) (int /*<<< orphan*/ ,int*,int) ;int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int*,int) ; 
 int w1_read_8 (struct w1_master*) ; 

u8 w1_read_block(struct w1_master *dev, u8 *buf, int len)
{
	int i;
	u8 ret;

	if (dev->bus_master->read_block)
		ret = dev->bus_master->read_block(dev->bus_master->data, buf, len);
	else {
		for (i = 0; i < len; ++i)
			buf[i] = w1_read_8(dev);
		ret = len;
	}

	return ret;
}