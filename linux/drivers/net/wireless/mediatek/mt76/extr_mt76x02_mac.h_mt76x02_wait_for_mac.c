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
struct mt76_dev {TYPE_1__* bus; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int (* rr ) (struct mt76_dev*,int const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_REMOVED ; 
 int stub1 (struct mt76_dev*,int const) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline bool mt76x02_wait_for_mac(struct mt76_dev *dev)
{
	const u32 MAC_CSR0 = 0x1000;
	int i;

	for (i = 0; i < 500; i++) {
		if (test_bit(MT76_REMOVED, &dev->state))
			return false;

		switch (dev->bus->rr(dev, MAC_CSR0)) {
		case 0:
		case ~0:
			break;
		default:
			return true;
		}
		usleep_range(5000, 10000);
	}
	return false;
}