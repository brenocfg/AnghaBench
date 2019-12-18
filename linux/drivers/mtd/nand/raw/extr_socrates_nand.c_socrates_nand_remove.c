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
struct socrates_nand_host {int /*<<< orphan*/  io_base; int /*<<< orphan*/  nand_chip; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct socrates_nand_host* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int socrates_nand_remove(struct platform_device *ofdev)
{
	struct socrates_nand_host *host = dev_get_drvdata(&ofdev->dev);

	nand_release(&host->nand_chip);

	iounmap(host->io_base);

	return 0;
}