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
struct tegra_hsp {int /*<<< orphan*/  mbox; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_controller_unregister (int /*<<< orphan*/ *) ; 
 struct tegra_hsp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tegra_hsp_remove_doorbells (struct tegra_hsp*) ; 

__attribute__((used)) static int tegra_hsp_remove(struct platform_device *pdev)
{
	struct tegra_hsp *hsp = platform_get_drvdata(pdev);

	mbox_controller_unregister(&hsp->mbox);
	tegra_hsp_remove_doorbells(hsp);

	return 0;
}