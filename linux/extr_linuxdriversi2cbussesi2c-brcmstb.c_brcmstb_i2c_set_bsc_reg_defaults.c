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
typedef  int /*<<< orphan*/  u32 ;
struct brcmstb_i2c_dev {TYPE_1__* bsc_regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctlhi_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSC_CTLHI_REG_DATAREG_SIZE_MASK ; 
 int brcmstb_i2c_get_data_regsz (struct brcmstb_i2c_dev*) ; 
 int /*<<< orphan*/  brcmstb_i2c_set_bus_speed (struct brcmstb_i2c_dev*) ; 
 int /*<<< orphan*/  bsc_writel (struct brcmstb_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctlhi_reg ; 

__attribute__((used)) static void brcmstb_i2c_set_bsc_reg_defaults(struct brcmstb_i2c_dev *dev)
{
	if (brcmstb_i2c_get_data_regsz(dev) == sizeof(u32))
		/* set 4 byte data in/out xfers  */
		dev->bsc_regmap->ctlhi_reg = BSC_CTLHI_REG_DATAREG_SIZE_MASK;
	else
		dev->bsc_regmap->ctlhi_reg &= ~BSC_CTLHI_REG_DATAREG_SIZE_MASK;

	bsc_writel(dev, dev->bsc_regmap->ctlhi_reg, ctlhi_reg);
	/* set bus speed */
	brcmstb_i2c_set_bus_speed(dev);
}