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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mfd_cell {size_t id; } ;
struct asic3 {int /*<<< orphan*/ * clocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  asic3_clk_enable (struct asic3*,int /*<<< orphan*/ *) ; 
 size_t* clock_ledn ; 
 struct asic3* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct mfd_cell* mfd_get_cell (struct platform_device*) ; 

__attribute__((used)) static int asic3_leds_enable(struct platform_device *pdev)
{
	const struct mfd_cell *cell = mfd_get_cell(pdev);
	struct asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	asic3_clk_enable(asic, &asic->clocks[clock_ledn[cell->id]]);

	return 0;
}