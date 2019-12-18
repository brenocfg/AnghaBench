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
struct sh_flctl {int /*<<< orphan*/  chip; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  flctl_release_dma (struct sh_flctl*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct sh_flctl* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flctl_remove(struct platform_device *pdev)
{
	struct sh_flctl *flctl = platform_get_drvdata(pdev);

	flctl_release_dma(flctl);
	nand_release(&flctl->chip);
	pm_runtime_disable(&pdev->dev);

	return 0;
}