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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dpi_data {int dummy; } ;

/* Variables and functions */
 struct dpi_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dpi_data *dpi_get_data_from_pdev(struct platform_device *pdev)
{
	return dev_get_drvdata(&pdev->dev);
}