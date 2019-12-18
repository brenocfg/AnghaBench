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
typedef  int u16 ;
struct mt9v111_dev {int /*<<< orphan*/  sd; int /*<<< orphan*/  dev; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int EIO ; 
 int MT9V111_CHIP_ID_HIGH ; 
 int MT9V111_CHIP_ID_LOW ; 
 int /*<<< orphan*/  MT9V111_CORE_RFF_CHIP_VER ; 
 int /*<<< orphan*/  MT9V111_R01_CORE ; 
 int /*<<< orphan*/  __mt9v111_power_off (int /*<<< orphan*/ *) ; 
 int __mt9v111_power_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int mt9v111_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mt9v111_chip_probe(struct mt9v111_dev *mt9v111)
{
	int ret;
	u16 val;

	ret = __mt9v111_power_on(&mt9v111->sd);
	if (ret)
		return ret;

	ret = mt9v111_read(mt9v111->client, MT9V111_R01_CORE,
			   MT9V111_CORE_RFF_CHIP_VER, &val);
	if (ret)
		goto power_off;

	if ((val >> 8) != MT9V111_CHIP_ID_HIGH &&
	    (val & 0xff) != MT9V111_CHIP_ID_LOW) {
		dev_err(mt9v111->dev,
			"Unable to identify MT9V111 chip: 0x%2x%2x\n",
			val >> 8, val & 0xff);
		ret = -EIO;
		goto power_off;
	}

	dev_dbg(mt9v111->dev, "Chip identified: 0x%2x%2x\n",
		val >> 8, val & 0xff);

power_off:
	__mt9v111_power_off(&mt9v111->sd);

	return ret;
}