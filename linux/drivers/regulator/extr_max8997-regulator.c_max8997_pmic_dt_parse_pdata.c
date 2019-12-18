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
struct max8997_platform_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int max8997_pmic_dt_parse_pdata(struct platform_device *pdev,
					struct max8997_platform_data *pdata)
{
	return 0;
}