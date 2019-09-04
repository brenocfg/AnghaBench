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
struct asic3 {scalar_t__ bus_shift; int /*<<< orphan*/  tmio_cnf; } ;

/* Variables and functions */
 struct asic3* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmio_core_mmc_pwr (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void asic3_mmc_pwr(struct platform_device *pdev, int state)
{
	struct asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	tmio_core_mmc_pwr(asic->tmio_cnf, 1 - asic->bus_shift, state);
}