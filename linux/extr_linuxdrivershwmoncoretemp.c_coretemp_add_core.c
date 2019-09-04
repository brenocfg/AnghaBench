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

/* Variables and functions */
 scalar_t__ create_core_data (struct platform_device*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 

__attribute__((used)) static void
coretemp_add_core(struct platform_device *pdev, unsigned int cpu, int pkg_flag)
{
	if (create_core_data(pdev, cpu, pkg_flag))
		dev_err(&pdev->dev, "Adding Core %u failed\n", cpu);
}