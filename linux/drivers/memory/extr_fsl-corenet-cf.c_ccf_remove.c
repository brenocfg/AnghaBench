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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ccf_private {TYPE_2__* err_regs; TYPE_1__* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  errinten; int /*<<< orphan*/  errdis; } ;
struct TYPE_3__ {int version; } ;

/* Variables and functions */
#define  CCF1 129 
#define  CCF2 128 
 struct ccf_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccf_remove(struct platform_device *pdev)
{
	struct ccf_private *ccf = dev_get_drvdata(&pdev->dev);

	switch (ccf->info->version) {
	case CCF1:
		iowrite32be(0, &ccf->err_regs->errdis);
		break;

	case CCF2:
		/*
		 * We clear errdis on ccf1 because that's the only way to
		 * disable interrupts, but on ccf2 there's no need to disable
		 * detection.
		 */
		iowrite32be(0, &ccf->err_regs->errinten);
		break;
	}

	return 0;
}