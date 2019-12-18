#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_usb2_platform_data {int /*<<< orphan*/  (* exit ) (struct platform_device*) ;} ;
struct TYPE_5__ {TYPE_2__* otg; } ;
struct TYPE_6__ {TYPE_1__ phy; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_OTG_MAJOR ; 
 int /*<<< orphan*/  FSL_OTG_NAME ; 
 struct fsl_usb2_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* fsl_otg_dev ; 
 int /*<<< orphan*/  fsl_otg_uninit_timers () ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_dr_regs ; 
 int /*<<< orphan*/  usb_remove_phy (TYPE_1__*) ; 

__attribute__((used)) static int fsl_otg_remove(struct platform_device *pdev)
{
	struct fsl_usb2_platform_data *pdata = dev_get_platdata(&pdev->dev);

	usb_remove_phy(&fsl_otg_dev->phy);
	free_irq(fsl_otg_dev->irq, fsl_otg_dev);

	iounmap((void *)usb_dr_regs);

	fsl_otg_uninit_timers();
	kfree(fsl_otg_dev->phy.otg);
	kfree(fsl_otg_dev);

	unregister_chrdev(FSL_OTG_MAJOR, FSL_OTG_NAME);

	if (pdata->exit)
		pdata->exit(pdev);

	return 0;
}