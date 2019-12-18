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
struct tc6393xb {scalar_t__ scr; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int start; } ;

/* Variables and functions */
 struct tc6393xb* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_2__* tc6393xb_mmc_resources ; 
 int /*<<< orphan*/  tmio_core_mmc_resume (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tc6393xb_mmc_resume(struct platform_device *mmc)
{
	struct tc6393xb *tc6393xb = dev_get_drvdata(mmc->dev.parent);

	tmio_core_mmc_resume(tc6393xb->scr + 0x200, 0,
		tc6393xb_mmc_resources[0].start & 0xfffe);

	return 0;
}