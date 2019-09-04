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

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_READ_GPIO ; 
 int /*<<< orphan*/  PMAC_FTR_WRITE_GPIO ; 
 int /*<<< orphan*/  core99_tb_gpio ; 
 int /*<<< orphan*/  pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smp_core99_gpio_tb_freeze(int freeze)
{
	if (freeze)
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, core99_tb_gpio, 4);
	else
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, core99_tb_gpio, 0);
	pmac_call_feature(PMAC_FTR_READ_GPIO, NULL, core99_tb_gpio, 0);
}