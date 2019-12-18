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
typedef  int u32 ;
struct s3c2410_wdt {int /*<<< orphan*/  dev; TYPE_1__* drv_data; int /*<<< orphan*/  pmureg; } ;
struct TYPE_2__ {int mask_bit; int quirks; int /*<<< orphan*/  mask_reset_reg; int /*<<< orphan*/  disable_reg; } ;

/* Variables and functions */
 int QUIRK_HAS_PMU_CONFIG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int s3c2410wdt_mask_and_disable_reset(struct s3c2410_wdt *wdt, bool mask)
{
	int ret;
	u32 mask_val = 1 << wdt->drv_data->mask_bit;
	u32 val = 0;

	/* No need to do anything if no PMU CONFIG needed */
	if (!(wdt->drv_data->quirks & QUIRK_HAS_PMU_CONFIG))
		return 0;

	if (mask)
		val = mask_val;

	ret = regmap_update_bits(wdt->pmureg,
			wdt->drv_data->disable_reg,
			mask_val, val);
	if (ret < 0)
		goto error;

	ret = regmap_update_bits(wdt->pmureg,
			wdt->drv_data->mask_reset_reg,
			mask_val, val);
 error:
	if (ret < 0)
		dev_err(wdt->dev, "failed to update reg(%d)\n", ret);

	return ret;
}