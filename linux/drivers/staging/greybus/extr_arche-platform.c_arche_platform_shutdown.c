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
struct arche_platform_drvdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arche_platform_poweroff_seq (struct arche_platform_drvdata*) ; 
 struct arche_platform_drvdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb3613_hub_mode_ctrl (int) ; 

__attribute__((used)) static void arche_platform_shutdown(struct platform_device *pdev)
{
	struct arche_platform_drvdata *arche_pdata = platform_get_drvdata(pdev);

	arche_platform_poweroff_seq(arche_pdata);

	usb3613_hub_mode_ctrl(false);
}