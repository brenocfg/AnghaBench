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
struct zynqmp_ipi_pdata {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct zynqmp_ipi_pdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  zynqmp_ipi_free_mboxes (struct zynqmp_ipi_pdata*) ; 

__attribute__((used)) static int zynqmp_ipi_remove(struct platform_device *pdev)
{
	struct zynqmp_ipi_pdata *pdata;

	pdata = platform_get_drvdata(pdev);
	zynqmp_ipi_free_mboxes(pdata);

	return 0;
}