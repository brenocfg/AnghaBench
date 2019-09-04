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
struct pca953x_chip {int /*<<< orphan*/  reg_direction; TYPE_1__* regs; int /*<<< orphan*/  reg_output; } ;
struct TYPE_2__ {int /*<<< orphan*/  direction; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int MAX_BANK ; 
 int /*<<< orphan*/  NBANK (struct pca953x_chip*) ; 
 int /*<<< orphan*/  PCA957X_BKEN ; 
 int /*<<< orphan*/  PCA957X_INVRT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int pca953x_read_regs (struct pca953x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pca953x_write_regs (struct pca953x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ pca957x_regs ; 

__attribute__((used)) static int device_pca957x_init(struct pca953x_chip *chip, u32 invert)
{
	int ret;
	u8 val[MAX_BANK];

	chip->regs = &pca957x_regs;

	ret = pca953x_read_regs(chip, chip->regs->output, chip->reg_output);
	if (ret)
		goto out;
	ret = pca953x_read_regs(chip, chip->regs->direction,
				chip->reg_direction);
	if (ret)
		goto out;

	/* set platform specific polarity inversion */
	if (invert)
		memset(val, 0xFF, NBANK(chip));
	else
		memset(val, 0, NBANK(chip));
	ret = pca953x_write_regs(chip, PCA957X_INVRT, val);
	if (ret)
		goto out;

	/* To enable register 6, 7 to control pull up and pull down */
	memset(val, 0x02, NBANK(chip));
	ret = pca953x_write_regs(chip, PCA957X_BKEN, val);
	if (ret)
		goto out;

	return 0;
out:
	return ret;
}