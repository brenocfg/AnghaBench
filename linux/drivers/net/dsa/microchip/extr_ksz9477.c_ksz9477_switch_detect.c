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
typedef  int u32 ;
struct ksz_device {int mib_port_cnt; int phy_port_cnt; int chip_id; int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  GBIT_SUPPORT ; 
 int /*<<< orphan*/  IS_9893 ; 
 int /*<<< orphan*/  NEW_XMII ; 
 int /*<<< orphan*/  REG_CHIP_ID0__1 ; 
 int /*<<< orphan*/  REG_GLOBAL_OPTIONS ; 
 int /*<<< orphan*/  REG_SW_GLOBAL_SERIAL_CTRL_0 ; 
 int SPI_AUTO_EDGE_DETECTION ; 
 int SW_GIGABIT_ABLE ; 
 int SW_QW_ABLE ; 
 int TOTAL_PORT_NUM ; 
 int ksz_read32 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 
 int ksz_read8 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 
 int ksz_write8 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ksz9477_switch_detect(struct ksz_device *dev)
{
	u8 data8;
	u8 id_hi;
	u8 id_lo;
	u32 id32;
	int ret;

	/* turn off SPI DO Edge select */
	ret = ksz_read8(dev, REG_SW_GLOBAL_SERIAL_CTRL_0, &data8);
	if (ret)
		return ret;

	data8 &= ~SPI_AUTO_EDGE_DETECTION;
	ret = ksz_write8(dev, REG_SW_GLOBAL_SERIAL_CTRL_0, data8);
	if (ret)
		return ret;

	/* read chip id */
	ret = ksz_read32(dev, REG_CHIP_ID0__1, &id32);
	if (ret)
		return ret;
	ret = ksz_read8(dev, REG_GLOBAL_OPTIONS, &data8);
	if (ret)
		return ret;

	/* Number of ports can be reduced depending on chip. */
	dev->mib_port_cnt = TOTAL_PORT_NUM;
	dev->phy_port_cnt = 5;

	/* Default capability is gigabit capable. */
	dev->features = GBIT_SUPPORT;

	id_hi = (u8)(id32 >> 16);
	id_lo = (u8)(id32 >> 8);
	if ((id_lo & 0xf) == 3) {
		/* Chip is from KSZ9893 design. */
		dev->features |= IS_9893;

		/* Chip does not support gigabit. */
		if (data8 & SW_QW_ABLE)
			dev->features &= ~GBIT_SUPPORT;
		dev->mib_port_cnt = 3;
		dev->phy_port_cnt = 2;
	} else {
		/* Chip uses new XMII register definitions. */
		dev->features |= NEW_XMII;

		/* Chip does not support gigabit. */
		if (!(data8 & SW_GIGABIT_ABLE))
			dev->features &= ~GBIT_SUPPORT;
	}

	/* Change chip id to known ones so it can be matched against them. */
	id32 = (id_hi << 16) | (id_lo << 8);

	dev->chip_id = id32;

	return 0;
}