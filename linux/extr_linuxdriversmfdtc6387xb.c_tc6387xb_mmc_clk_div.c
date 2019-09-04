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
 struct tc6387xb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tmio_core_mmc_clk_div (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc6387xb_mmc_clk_div(struct platform_device *mmc, int state)
{
	struct platform_device *dev = to_platform_device(mmc->dev.parent);
	struct tc6387xb *tc6387xb = platform_get_drvdata(dev);

	tmio_core_mmc_clk_div(tc6387xb->scr + 0x200, 0, state);
}