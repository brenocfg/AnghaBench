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
typedef  int u32 ;
struct mei_txe_hw {int dummy; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SATT2_BRG_BA_LSB_REG ; 
 int SATT2_CTRL_BR_BASE_ADDR_REG_SHIFT ; 
 int /*<<< orphan*/  SATT2_CTRL_REG ; 
 int SATT2_CTRL_VALID_MSK ; 
 int /*<<< orphan*/  SATT2_SAP_SIZE_REG ; 
 int SATT_RANGE_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_txe_br_reg_write (struct mei_txe_hw*,int /*<<< orphan*/ ,int) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

int mei_txe_setup_satt2(struct mei_device *dev, phys_addr_t addr, u32 range)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);

	u32 lo32 = lower_32_bits(addr);
	u32 hi32 = upper_32_bits(addr);
	u32 ctrl;

	/* SATT is limited to 36 Bits */
	if (hi32 & ~0xF)
		return -EINVAL;

	/* SATT has to be 16Byte aligned */
	if (lo32 & 0xF)
		return -EINVAL;

	/* SATT range has to be 4Bytes aligned */
	if (range & 0x4)
		return -EINVAL;

	/* SATT is limited to 32 MB range*/
	if (range > SATT_RANGE_MAX)
		return -EINVAL;

	ctrl = SATT2_CTRL_VALID_MSK;
	ctrl |= hi32  << SATT2_CTRL_BR_BASE_ADDR_REG_SHIFT;

	mei_txe_br_reg_write(hw, SATT2_SAP_SIZE_REG, range);
	mei_txe_br_reg_write(hw, SATT2_BRG_BA_LSB_REG, lo32);
	mei_txe_br_reg_write(hw, SATT2_CTRL_REG, ctrl);
	dev_dbg(dev->dev, "SATT2: SAP_SIZE_OFFSET=0x%08X, BRG_BA_LSB_OFFSET=0x%08X, CTRL_OFFSET=0x%08X\n",
		range, lo32, ctrl);

	return 0;
}