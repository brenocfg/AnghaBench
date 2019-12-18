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
struct bcm47xxnflash {int /*<<< orphan*/  nand_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct bcm47xxnflash* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int bcm47xxnflash_remove(struct platform_device *pdev)
{
	struct bcm47xxnflash *nflash = platform_get_drvdata(pdev);

	nand_release(&nflash->nand_chip);

	return 0;
}