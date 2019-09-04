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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ksz_device {int /*<<< orphan*/  chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CHIP_ID0__1 ; 
 int /*<<< orphan*/  REG_SW_GLOBAL_SERIAL_CTRL_0 ; 
 int /*<<< orphan*/  SPI_AUTO_EDGE_DETECTION ; 
 int ksz_read32 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ksz_read8 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ksz_write8 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ksz_switch_detect(struct ksz_device *dev)
{
	u8 data8;
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

	dev->chip_id = id32;

	return 0;
}