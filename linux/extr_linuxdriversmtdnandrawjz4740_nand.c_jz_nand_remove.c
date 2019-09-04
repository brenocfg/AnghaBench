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
struct platform_device {int dummy; } ;
struct jz_nand {unsigned char* banks; scalar_t__ base; int /*<<< orphan*/  mem; scalar_t__* bank_base; int /*<<< orphan*/ * bank_mem; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 size_t JZ_NAND_NUM_BANKS ; 
 scalar_t__ JZ_REG_NAND_CTRL ; 
 int /*<<< orphan*/  jz_nand_iounmap_resource (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct jz_nand*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (int /*<<< orphan*/ *) ; 
 struct jz_nand* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int jz_nand_remove(struct platform_device *pdev)
{
	struct jz_nand *nand = platform_get_drvdata(pdev);
	size_t i;

	nand_release(nand_to_mtd(&nand->chip));

	/* Deassert and disable all chips */
	writel(0, nand->base + JZ_REG_NAND_CTRL);

	for (i = 0; i < JZ_NAND_NUM_BANKS; ++i) {
		unsigned char bank = nand->banks[i];
		if (bank != 0) {
			jz_nand_iounmap_resource(nand->bank_mem[bank - 1],
						 nand->bank_base[bank - 1]);
		}
	}

	jz_nand_iounmap_resource(nand->mem, nand->base);

	kfree(nand);

	return 0;
}