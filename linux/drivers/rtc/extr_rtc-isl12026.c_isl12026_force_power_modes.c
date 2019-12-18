#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISL12026_REG_PWR ; 
 int ISL12026_REG_PWR_BSW ; 
 int ISL12026_REG_PWR_SBIB ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 int isl12026_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isl12026_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 

__attribute__((used)) static void isl12026_force_power_modes(struct i2c_client *client)
{
	int ret;
	int pwr, requested_pwr;
	u32 bsw_val, sbib_val;
	bool set_bsw, set_sbib;

	/*
	 * If we can read the of_property, set the specified value.
	 * If there is an error reading the of_property (likely
	 * because it does not exist), keep the current value.
	 */
	ret = of_property_read_u32(client->dev.of_node,
				   "isil,pwr-bsw", &bsw_val);
	set_bsw = (ret == 0);

	ret = of_property_read_u32(client->dev.of_node,
				   "isil,pwr-sbib", &sbib_val);
	set_sbib = (ret == 0);

	/* Check if PWR.BSW and/or PWR.SBIB need specified values */
	if (!set_bsw && !set_sbib)
		return;

	pwr = isl12026_read_reg(client, ISL12026_REG_PWR);
	if (pwr < 0) {
		dev_warn(&client->dev, "Error: Failed to read PWR %d\n", pwr);
		return;
	}

	requested_pwr = pwr;

	if (set_bsw) {
		if (bsw_val)
			requested_pwr |= ISL12026_REG_PWR_BSW;
		else
			requested_pwr &= ~ISL12026_REG_PWR_BSW;
	} /* else keep current BSW */

	if (set_sbib) {
		if (sbib_val)
			requested_pwr |= ISL12026_REG_PWR_SBIB;
		else
			requested_pwr &= ~ISL12026_REG_PWR_SBIB;
	} /* else keep current SBIB */

	if (pwr >= 0 && pwr != requested_pwr) {
		dev_dbg(&client->dev, "PWR: %02x\n", pwr);
		dev_dbg(&client->dev, "Updating PWR to: %02x\n", requested_pwr);
		isl12026_write_reg(client, ISL12026_REG_PWR, requested_pwr);
	}
}