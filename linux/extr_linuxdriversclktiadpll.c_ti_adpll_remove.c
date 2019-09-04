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
struct ti_adpll_data {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ti_adpll_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_adpll_free_resources (struct ti_adpll_data*) ; 

__attribute__((used)) static int ti_adpll_remove(struct platform_device *pdev)
{
	struct ti_adpll_data *d = dev_get_drvdata(&pdev->dev);

	ti_adpll_free_resources(d);

	return 0;
}