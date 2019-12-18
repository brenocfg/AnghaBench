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
struct dbx500_regulator_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int ux500_regulator_debug_init(struct platform_device *pdev,
			     struct dbx500_regulator_info *regulator_info,
			     int num_regulators)
{
	return 0;
}