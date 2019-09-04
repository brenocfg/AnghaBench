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
struct twl4030_madc_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_BCI_BCICTL1 ; 
 int TWL4030_BCI_ITHEN ; 
 int TWL4030_BCI_TYPEN ; 
 int /*<<< orphan*/  TWL_MODULE_MAIN_CHARGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_madc_set_current_generator(struct twl4030_madc_data *madc,
					      int chan, int on)
{
	int ret;
	int regmask;
	u8 regval;

	ret = twl_i2c_read_u8(TWL_MODULE_MAIN_CHARGE,
			      &regval, TWL4030_BCI_BCICTL1);
	if (ret) {
		dev_err(madc->dev, "unable to read BCICTL1 reg 0x%X",
			TWL4030_BCI_BCICTL1);
		return ret;
	}

	regmask = chan ? TWL4030_BCI_ITHEN : TWL4030_BCI_TYPEN;
	if (on)
		regval |= regmask;
	else
		regval &= ~regmask;

	ret = twl_i2c_write_u8(TWL_MODULE_MAIN_CHARGE,
			       regval, TWL4030_BCI_BCICTL1);
	if (ret) {
		dev_err(madc->dev, "unable to write BCICTL1 reg 0x%X\n",
			TWL4030_BCI_BCICTL1);
		return ret;
	}

	return 0;
}