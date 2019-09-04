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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ksz_device {int dummy; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
 int BROADCAST_STORM_PROT_RATE ; 
 int BROADCAST_STORM_RATE ; 
 int BROADCAST_STORM_VALUE ; 
 int /*<<< orphan*/  REG_SW_GLOBAL_SERIAL_CTRL_0 ; 
 int /*<<< orphan*/  REG_SW_INT_MASK__4 ; 
 int /*<<< orphan*/  REG_SW_LUE_CTRL_1 ; 
 int /*<<< orphan*/  REG_SW_MAC_CTRL_2 ; 
 int /*<<< orphan*/  REG_SW_OPERATION ; 
 int /*<<< orphan*/  REG_SW_PORT_INT_MASK__4 ; 
 int /*<<< orphan*/  REG_SW_PORT_INT_STATUS__4 ; 
 int SPI_AUTO_EDGE_DETECTION ; 
 int SWITCH_INT_MASK ; 
 int SW_AGING_ENABLE ; 
 int SW_FLUSH_MSTP_TABLE ; 
 int SW_FLUSH_STP_TABLE ; 
 int SW_LINK_AUTO_AGING ; 
 int /*<<< orphan*/  SW_RESET ; 
 int SW_SRC_ADDR_FILTER ; 
 int /*<<< orphan*/  ksz_cfg (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_read16 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_read32 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz_read8 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_write16 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_write32 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_write8 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ksz_reset_switch(struct dsa_switch *ds)
{
	struct ksz_device *dev = ds->priv;
	u8 data8;
	u16 data16;
	u32 data32;

	/* reset switch */
	ksz_cfg(dev, REG_SW_OPERATION, SW_RESET, true);

	/* turn off SPI DO Edge select */
	ksz_read8(dev, REG_SW_GLOBAL_SERIAL_CTRL_0, &data8);
	data8 &= ~SPI_AUTO_EDGE_DETECTION;
	ksz_write8(dev, REG_SW_GLOBAL_SERIAL_CTRL_0, data8);

	/* default configuration */
	ksz_read8(dev, REG_SW_LUE_CTRL_1, &data8);
	data8 = SW_AGING_ENABLE | SW_LINK_AUTO_AGING |
	      SW_SRC_ADDR_FILTER | SW_FLUSH_STP_TABLE | SW_FLUSH_MSTP_TABLE;
	ksz_write8(dev, REG_SW_LUE_CTRL_1, data8);

	/* disable interrupts */
	ksz_write32(dev, REG_SW_INT_MASK__4, SWITCH_INT_MASK);
	ksz_write32(dev, REG_SW_PORT_INT_MASK__4, 0x7F);
	ksz_read32(dev, REG_SW_PORT_INT_STATUS__4, &data32);

	/* set broadcast storm protection 10% rate */
	ksz_read16(dev, REG_SW_MAC_CTRL_2, &data16);
	data16 &= ~BROADCAST_STORM_RATE;
	data16 |= (BROADCAST_STORM_VALUE * BROADCAST_STORM_PROT_RATE) / 100;
	ksz_write16(dev, REG_SW_MAC_CTRL_2, data16);

	return 0;
}