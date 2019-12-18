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
typedef  int u16 ;
struct mt76x02_dev {TYPE_1__* beacon_ops; } ;
struct TYPE_2__ {int nslots; int slot_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_BCN_OFFSET (int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt76x02_set_beacon_offsets(struct mt76x02_dev *dev)
{
	u32 regs[4] = {};
	u16 val;
	int i;

	for (i = 0; i < dev->beacon_ops->nslots; i++) {
		val = i * dev->beacon_ops->slot_size;
		regs[i / 4] |= (val / 64) << (8 * (i % 4));
	}

	for (i = 0; i < 4; i++)
		mt76_wr(dev, MT_BCN_OFFSET(i), regs[i]);
}