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
struct dw_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_16BIT ; 
 int /*<<< orphan*/  ACCESS_SWAP ; 
 int /*<<< orphan*/  DW_IC_COMP_TYPE ; 
 int DW_IC_COMP_TYPE_VALUE ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 
 int i2c_dw_acquire_lock (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_dw_release_lock (struct dw_i2c_dev*) ; 
 int swab32 (int) ; 

int i2c_dw_set_reg_access(struct dw_i2c_dev *dev)
{
	u32 reg;
	int ret;

	ret = i2c_dw_acquire_lock(dev);
	if (ret)
		return ret;

	reg = dw_readl(dev, DW_IC_COMP_TYPE);
	i2c_dw_release_lock(dev);

	if (reg == swab32(DW_IC_COMP_TYPE_VALUE)) {
		/* Configure register endianess access */
		dev->flags |= ACCESS_SWAP;
	} else if (reg == (DW_IC_COMP_TYPE_VALUE & 0x0000ffff)) {
		/* Configure register access mode 16bit */
		dev->flags |= ACCESS_16BIT;
	} else if (reg != DW_IC_COMP_TYPE_VALUE) {
		dev_err(dev->dev,
			"Unknown Synopsys component type: 0x%08x\n", reg);
		return -ENODEV;
	}

	return 0;
}