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
struct st_dwc3 {int /*<<< orphan*/  rstc_rst; int /*<<< orphan*/  rstc_pwrdn; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 
 struct st_dwc3* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_dwc3_remove(struct platform_device *pdev)
{
	struct st_dwc3 *dwc3_data = platform_get_drvdata(pdev);

	of_platform_depopulate(&pdev->dev);

	reset_control_assert(dwc3_data->rstc_pwrdn);
	reset_control_assert(dwc3_data->rstc_rst);

	return 0;
}