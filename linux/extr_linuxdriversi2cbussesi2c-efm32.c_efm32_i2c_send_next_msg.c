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
struct i2c_msg {int dummy; } ;
struct efm32_i2c_ddata {size_t current_msg; struct i2c_msg* msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CMD ; 
 int /*<<< orphan*/  REG_CMD_START ; 
 int /*<<< orphan*/  REG_TXDATA ; 
 int /*<<< orphan*/  efm32_i2c_write32 (struct efm32_i2c_ddata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_8bit_addr_from_msg (struct i2c_msg*) ; 

__attribute__((used)) static void efm32_i2c_send_next_msg(struct efm32_i2c_ddata *ddata)
{
	struct i2c_msg *cur_msg = &ddata->msgs[ddata->current_msg];

	efm32_i2c_write32(ddata, REG_CMD, REG_CMD_START);
	efm32_i2c_write32(ddata, REG_TXDATA, i2c_8bit_addr_from_msg(cur_msg));
}