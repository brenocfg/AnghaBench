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
struct ipu_soc {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_irq_exit (struct ipu_soc*) ; 
 int /*<<< orphan*/  ipu_submodules_exit (struct ipu_soc*) ; 
 int /*<<< orphan*/  platform_device_unregister_children (struct platform_device*) ; 
 struct ipu_soc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ipu_remove(struct platform_device *pdev)
{
	struct ipu_soc *ipu = platform_get_drvdata(pdev);

	platform_device_unregister_children(pdev);
	ipu_submodules_exit(ipu);
	ipu_irq_exit(ipu);

	clk_disable_unprepare(ipu->clk);

	return 0;
}