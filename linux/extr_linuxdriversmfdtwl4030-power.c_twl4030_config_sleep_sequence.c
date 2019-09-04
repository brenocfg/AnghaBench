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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  R_SEQ_ADD_A2S ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_config_sleep_sequence(u8 address)
{
	int err;

	/* Set ACTIVE to SLEEP SEQ address in T2 memory*/
	err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, address, R_SEQ_ADD_A2S);

	if (err)
		pr_err("TWL4030 sleep sequence config error\n");

	return err;
}