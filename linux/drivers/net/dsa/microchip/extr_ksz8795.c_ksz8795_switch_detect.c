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
typedef  int u8 ;
typedef  int u16 ;
struct ksz_device {int chip_id; scalar_t__ cpu_port; int /*<<< orphan*/  host_mask; scalar_t__ mib_port_cnt; void* port_cnt; void* last_port; void* phy_port_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int CHIP_ID_94 ; 
 int CHIP_ID_95 ; 
 int ENODEV ; 
 int FAMILY_ID ; 
 int PORT_FIBER_MODE ; 
 int /*<<< orphan*/  REG_CHIP_ID0 ; 
 int /*<<< orphan*/  REG_PORT_1_STATUS_0 ; 
 void* SWITCH_PORT_NUM ; 
 int SW_CHIP_ID_M ; 
 scalar_t__ TOTAL_PORT_NUM ; 
 int ksz_read16 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_read8 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ksz8795_switch_detect(struct ksz_device *dev)
{
	u8 id1, id2;
	u16 id16;
	int ret;

	/* read chip id */
	ret = ksz_read16(dev, REG_CHIP_ID0, &id16);
	if (ret)
		return ret;

	id1 = id16 >> 8;
	id2 = id16 & SW_CHIP_ID_M;
	if (id1 != FAMILY_ID ||
	    (id2 != CHIP_ID_94 && id2 != CHIP_ID_95))
		return -ENODEV;

	dev->mib_port_cnt = TOTAL_PORT_NUM;
	dev->phy_port_cnt = SWITCH_PORT_NUM;
	dev->port_cnt = SWITCH_PORT_NUM;

	if (id2 == CHIP_ID_95) {
		u8 val;

		id2 = 0x95;
		ksz_read8(dev, REG_PORT_1_STATUS_0, &val);
		if (val & PORT_FIBER_MODE)
			id2 = 0x65;
	} else if (id2 == CHIP_ID_94) {
		dev->port_cnt--;
		dev->last_port = dev->port_cnt;
		id2 = 0x94;
	}
	id16 &= ~0xff;
	id16 |= id2;
	dev->chip_id = id16;

	dev->cpu_port = dev->mib_port_cnt - 1;
	dev->host_mask = BIT(dev->cpu_port);

	return 0;
}