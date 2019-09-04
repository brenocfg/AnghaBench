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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct lan9303 {int /*<<< orphan*/  indirect_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAN9303_SWITCH_CSR_CMD ; 
 int /*<<< orphan*/  LAN9303_SWITCH_CSR_CMD_BUSY ; 
 int /*<<< orphan*/  LAN9303_SWITCH_CSR_CMD_LANES ; 
 int /*<<< orphan*/  LAN9303_SWITCH_CSR_CMD_RW ; 
 int /*<<< orphan*/  LAN9303_SWITCH_CSR_DATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int lan9303_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lan9303_switch_wait_for_completion (struct lan9303*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan9303_read_switch_reg(struct lan9303 *chip, u16 regnum, u32 *val)
{
	u32 reg;
	int ret;

	reg = regnum;
	reg |= LAN9303_SWITCH_CSR_CMD_LANES;
	reg |= LAN9303_SWITCH_CSR_CMD_RW;
	reg |= LAN9303_SWITCH_CSR_CMD_BUSY;

	mutex_lock(&chip->indirect_mutex);

	ret = lan9303_switch_wait_for_completion(chip);
	if (ret)
		goto on_error;

	/* trigger read */
	ret = regmap_write(chip->regmap, LAN9303_SWITCH_CSR_CMD, reg);
	if (ret) {
		dev_err(chip->dev, "Failed to write csr command reg: %d\n",
			ret);
		goto on_error;
	}

	ret = lan9303_switch_wait_for_completion(chip);
	if (ret)
		goto on_error;

	ret = lan9303_read(chip->regmap, LAN9303_SWITCH_CSR_DATA, val);
	if (ret)
		dev_err(chip->dev, "Failed to read csr data reg: %d\n", ret);
on_error:
	mutex_unlock(&chip->indirect_mutex);
	return ret;
}