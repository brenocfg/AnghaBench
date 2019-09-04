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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ge_b850v3_lvds_remove () ; 

__attribute__((used)) static int stdp4028_ge_b850v3_fw_remove(struct i2c_client *stdp4028_i2c)
{
	ge_b850v3_lvds_remove();

	return 0;
}