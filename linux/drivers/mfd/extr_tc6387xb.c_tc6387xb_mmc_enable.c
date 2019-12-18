#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tc6387xb {scalar_t__ scr; int /*<<< orphan*/  clk32k; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct tc6387xb* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_2__* tc6387xb_mmc_resources ; 
 int /*<<< orphan*/  tmio_core_mmc_enable (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tc6387xb_mmc_enable(struct platform_device *mmc)
{
	struct tc6387xb *tc6387xb = dev_get_drvdata(mmc->dev.parent);

	clk_prepare_enable(tc6387xb->clk32k);

	tmio_core_mmc_enable(tc6387xb->scr + 0x200, 0,
		tc6387xb_mmc_resources[0].start & 0xfffe);

	return 0;
}