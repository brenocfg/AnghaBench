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
 int /*<<< orphan*/ * msp430 ; 
 int /*<<< orphan*/ * pm_power_off ; 

__attribute__((used)) static int dm355evm_msp_remove(struct i2c_client *client)
{
	pm_power_off = NULL;
	msp430 = NULL;
	return 0;
}