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
struct nuc900_nand {int /*<<< orphan*/  clk; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (int /*<<< orphan*/ *) ; 
 struct nuc900_nand* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int nuc900_nand_remove(struct platform_device *pdev)
{
	struct nuc900_nand *nuc900_nand = platform_get_drvdata(pdev);

	nand_release(nand_to_mtd(&nuc900_nand->chip));
	clk_disable(nuc900_nand->clk);

	return 0;
}