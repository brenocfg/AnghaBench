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
typedef  int u8 ;

/* Variables and functions */
 int TWL4030_BCIAUTOWEN ; 
 int TWL4030_CONFIG_DONE ; 
 int /*<<< orphan*/  TWL4030_PM_MASTER_BOOT_BCI ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 int twl4030_clear_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_clear_set_boot_bci(u8 clear, u8 set)
{
	return twl4030_clear_set(TWL_MODULE_PM_MASTER, clear,
			TWL4030_CONFIG_DONE | TWL4030_BCIAUTOWEN | set,
			TWL4030_PM_MASTER_BOOT_BCI);
}