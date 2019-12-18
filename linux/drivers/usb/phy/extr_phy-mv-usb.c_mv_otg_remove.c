#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int dummy; } ;
struct mv_otg {int /*<<< orphan*/  phy; scalar_t__ qwork; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  mv_otg_disable (struct mv_otg*) ; 
 struct mv_otg* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv_otg_remove(struct platform_device *pdev)
{
	struct mv_otg *mvotg = platform_get_drvdata(pdev);

	if (mvotg->qwork) {
		flush_workqueue(mvotg->qwork);
		destroy_workqueue(mvotg->qwork);
	}

	mv_otg_disable(mvotg);

	usb_remove_phy(&mvotg->phy);

	return 0;
}