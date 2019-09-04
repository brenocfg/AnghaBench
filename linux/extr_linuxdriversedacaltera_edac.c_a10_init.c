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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A10_INTMODE_OFST ; 
 int /*<<< orphan*/  A10_INTMODE_SB_INT ; 
 int /*<<< orphan*/  A10_SERRCNTREG_OFST ; 
 int /*<<< orphan*/  EDAC_MC ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int a10_init(struct regmap *mc_vbase)
{
	if (regmap_update_bits(mc_vbase, A10_INTMODE_OFST,
			       A10_INTMODE_SB_INT, A10_INTMODE_SB_INT)) {
		edac_printk(KERN_ERR, EDAC_MC,
			    "Error setting SB IRQ mode\n");
		return -ENODEV;
	}

	if (regmap_write(mc_vbase, A10_SERRCNTREG_OFST, 1)) {
		edac_printk(KERN_ERR, EDAC_MC,
			    "Error setting trigger count\n");
		return -ENODEV;
	}

	return 0;
}