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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtd; } ;
struct nxp_spifi {int /*<<< orphan*/  clk_reg; int /*<<< orphan*/  clk_spifi; TYPE_1__ nor; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct nxp_spifi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int nxp_spifi_remove(struct platform_device *pdev)
{
	struct nxp_spifi *spifi = platform_get_drvdata(pdev);

	mtd_device_unregister(&spifi->nor.mtd);
	clk_disable_unprepare(spifi->clk_spifi);
	clk_disable_unprepare(spifi->clk_reg);

	return 0;
}