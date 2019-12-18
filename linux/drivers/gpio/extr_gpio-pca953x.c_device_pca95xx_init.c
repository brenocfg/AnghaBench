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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct pca953x_chip {TYPE_1__* regs; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  invert; scalar_t__ direction; scalar_t__ output; } ;

/* Variables and functions */
 int MAX_BANK ; 
 scalar_t__ NBANK (struct pca953x_chip*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int pca953x_write_regs (struct pca953x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regcache_sync_region (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int device_pca95xx_init(struct pca953x_chip *chip, u32 invert)
{
	int ret;
	u8 val[MAX_BANK];

	ret = regcache_sync_region(chip->regmap, chip->regs->output,
				   chip->regs->output + NBANK(chip));
	if (ret)
		goto out;

	ret = regcache_sync_region(chip->regmap, chip->regs->direction,
				   chip->regs->direction + NBANK(chip));
	if (ret)
		goto out;

	/* set platform specific polarity inversion */
	if (invert)
		memset(val, 0xFF, NBANK(chip));
	else
		memset(val, 0, NBANK(chip));

	ret = pca953x_write_regs(chip, chip->regs->invert, val);
out:
	return ret;
}