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
struct tc6387xb {scalar_t__ scr; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct tc6387xb* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmio_core_mmc_clk_div (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tc6387xb_mmc_clk_div(struct platform_device *mmc, int state)
{
	struct tc6387xb *tc6387xb = dev_get_drvdata(mmc->dev.parent);

	tmio_core_mmc_clk_div(tc6387xb->scr + 0x200, 0, state);
}