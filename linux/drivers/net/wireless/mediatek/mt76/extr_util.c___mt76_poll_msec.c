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
typedef  int u32 ;
struct mt76_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {int (* rr ) (struct mt76_dev*,int) ;} ;

/* Variables and functions */
 int stub1 (struct mt76_dev*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

bool __mt76_poll_msec(struct mt76_dev *dev, u32 offset, u32 mask, u32 val,
		      int timeout)
{
	u32 cur;

	timeout /= 10;
	do {
		cur = dev->bus->rr(dev, offset) & mask;
		if (cur == val)
			return true;

		usleep_range(10000, 20000);
	} while (timeout-- > 0);

	return false;
}