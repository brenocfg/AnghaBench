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
struct cplds {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_set_chip_and_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cplds* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cplds_remove(struct platform_device *pdev)
{
	struct cplds *fpga = platform_get_drvdata(pdev);

	irq_set_chip_and_handler(fpga->irq, NULL, NULL);

	return 0;
}