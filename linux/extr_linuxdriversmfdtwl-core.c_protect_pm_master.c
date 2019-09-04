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
 int /*<<< orphan*/  TWL4030_PM_MASTER_PROTECT_KEY ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int protect_pm_master(void)
{
	int e = 0;

	e = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, 0,
			     TWL4030_PM_MASTER_PROTECT_KEY);
	return e;
}