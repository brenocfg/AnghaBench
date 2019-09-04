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
typedef  unsigned int u8 ;
struct max77620_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX77620_CID5_DIDM (unsigned int) ; 
 int MAX77620_REG_CID0 ; 
 int MAX77620_REG_CID5 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int max77620_read_es_version(struct max77620_chip *chip)
{
	unsigned int val;
	u8 cid_val[6];
	int i;
	int ret;

	for (i = MAX77620_REG_CID0; i <= MAX77620_REG_CID5; i++) {
		ret = regmap_read(chip->rmap, i, &val);
		if (ret < 0) {
			dev_err(chip->dev, "Failed to read CID: %d\n", ret);
			return ret;
		}
		dev_dbg(chip->dev, "CID%d: 0x%02x\n",
			i - MAX77620_REG_CID0, val);
		cid_val[i - MAX77620_REG_CID0] = val;
	}

	/* CID4 is OTP Version  and CID5 is ES version */
	dev_info(chip->dev, "PMIC Version OTP:0x%02X and ES:0x%X\n",
		 cid_val[4], MAX77620_CID5_DIDM(cid_val[5]));

	return ret;
}