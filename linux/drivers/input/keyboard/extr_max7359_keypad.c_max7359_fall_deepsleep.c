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
 int /*<<< orphan*/  MAX7359_AUTOSLEEP_8192 ; 
 int /*<<< orphan*/  MAX7359_REG_SLEEP ; 
 int /*<<< orphan*/  max7359_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void max7359_fall_deepsleep(struct i2c_client *client)
{
	max7359_write_reg(client, MAX7359_REG_SLEEP, MAX7359_AUTOSLEEP_8192);
}