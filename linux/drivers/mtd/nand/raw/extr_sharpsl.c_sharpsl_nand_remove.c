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
struct sharpsl_nand {int /*<<< orphan*/  io; int /*<<< orphan*/  chip; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sharpsl_nand*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct sharpsl_nand* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int sharpsl_nand_remove(struct platform_device *pdev)
{
	struct sharpsl_nand *sharpsl = platform_get_drvdata(pdev);

	/* Release resources, unregister device */
	nand_release(&sharpsl->chip);

	iounmap(sharpsl->io);

	/* Free the MTD device structure */
	kfree(sharpsl);

	return 0;
}