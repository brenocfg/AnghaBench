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
struct sc27xx_efuse {int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC27XX_EFUSE_POLL_DELAY_US ; 
 int /*<<< orphan*/  SC27XX_EFUSE_POLL_TIMEOUT ; 
 scalar_t__ SC27XX_EFUSE_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sc27xx_efuse_poll_status(struct sc27xx_efuse *efuse, u32 bits)
{
	int ret;
	u32 val;

	ret = regmap_read_poll_timeout(efuse->regmap,
				       efuse->base + SC27XX_EFUSE_STATUS,
				       val, (val & bits),
				       SC27XX_EFUSE_POLL_DELAY_US,
				       SC27XX_EFUSE_POLL_TIMEOUT);
	if (ret) {
		dev_err(efuse->dev, "timeout to update the efuse status\n");
		return ret;
	}

	return 0;
}