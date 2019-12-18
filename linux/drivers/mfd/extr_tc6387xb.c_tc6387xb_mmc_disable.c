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
struct tc6387xb {int /*<<< orphan*/  clk32k; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct tc6387xb* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc6387xb_mmc_disable(struct platform_device *mmc)
{
	struct tc6387xb *tc6387xb = dev_get_drvdata(mmc->dev.parent);

	clk_disable_unprepare(tc6387xb->clk32k);

	return 0;
}