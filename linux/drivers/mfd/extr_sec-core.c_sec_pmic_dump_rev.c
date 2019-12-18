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
struct sec_pmic_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap_pmic; } ;

/* Variables and functions */
 int /*<<< orphan*/  S2MPS11_REG_ID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void sec_pmic_dump_rev(struct sec_pmic_dev *sec_pmic)
{
	unsigned int val;

	/* For each device type, the REG_ID is always the first register */
	if (!regmap_read(sec_pmic->regmap_pmic, S2MPS11_REG_ID, &val))
		dev_dbg(sec_pmic->dev, "Revision: 0x%x\n", val);
}