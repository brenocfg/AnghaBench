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
struct lan9303 {int /*<<< orphan*/  dev; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENODEV ; 
 int LAN9303_CHIP_ID ; 
 int /*<<< orphan*/  LAN9303_CHIP_REV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int lan9303_detect_phy_setup (struct lan9303*) ; 
 int lan9303_disable_processing (struct lan9303*) ; 
 int lan9303_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lan9303_check_device(struct lan9303 *chip)
{
	int ret;
	u32 reg;

	ret = lan9303_read(chip->regmap, LAN9303_CHIP_REV, &reg);
	if (ret) {
		dev_err(chip->dev, "failed to read chip revision register: %d\n",
			ret);
		if (!chip->reset_gpio) {
			dev_dbg(chip->dev,
				"hint: maybe failed due to missing reset GPIO\n");
		}
		return ret;
	}

	if ((reg >> 16) != LAN9303_CHIP_ID) {
		dev_err(chip->dev, "expecting LAN9303 chip, but found: %X\n",
			reg >> 16);
		return -ENODEV;
	}

	/* The default state of the LAN9303 device is to forward packets between
	 * all ports (if not configured differently by an external EEPROM).
	 * The initial state of a DSA device must be forwarding packets only
	 * between the external and the internal ports and no forwarding
	 * between the external ports. In preparation we stop packet handling
	 * at all for now until the LAN9303 device is re-programmed accordingly.
	 */
	ret = lan9303_disable_processing(chip);
	if (ret)
		dev_warn(chip->dev, "failed to disable switching %d\n", ret);

	dev_info(chip->dev, "Found LAN9303 rev. %u\n", reg & 0xffff);

	ret = lan9303_detect_phy_setup(chip);
	if (ret) {
		dev_err(chip->dev,
			"failed to discover phy bootstrap setup: %d\n", ret);
		return ret;
	}

	return 0;
}