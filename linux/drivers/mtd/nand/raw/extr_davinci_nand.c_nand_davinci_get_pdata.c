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
struct davinci_nand_pdata {int dummy; } ;

/* Variables and functions */
 struct davinci_nand_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct davinci_nand_pdata
	*nand_davinci_get_pdata(struct platform_device *pdev)
{
	return dev_get_platdata(&pdev->dev);
}