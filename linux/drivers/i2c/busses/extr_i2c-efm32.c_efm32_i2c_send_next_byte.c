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
struct i2c_msg {scalar_t__ len; int /*<<< orphan*/ * buf; } ;
struct efm32_i2c_ddata {size_t current_msg; scalar_t__ current_word; int num_msgs; int /*<<< orphan*/  done; struct i2c_msg* msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CMD ; 
 int /*<<< orphan*/  REG_CMD_STOP ; 
 int /*<<< orphan*/  REG_TXDATA ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efm32_i2c_send_next_msg (struct efm32_i2c_ddata*) ; 
 int /*<<< orphan*/  efm32_i2c_write32 (struct efm32_i2c_ddata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efm32_i2c_send_next_byte(struct efm32_i2c_ddata *ddata)
{
	struct i2c_msg *cur_msg = &ddata->msgs[ddata->current_msg];

	if (ddata->current_word >= cur_msg->len) {
		/* cur_msg completely transferred */
		ddata->current_word = 0;
		ddata->current_msg += 1;

		if (ddata->current_msg >= ddata->num_msgs) {
			efm32_i2c_write32(ddata, REG_CMD, REG_CMD_STOP);
			complete(&ddata->done);
		} else {
			efm32_i2c_send_next_msg(ddata);
		}
	} else {
		efm32_i2c_write32(ddata, REG_TXDATA,
				cur_msg->buf[ddata->current_word++]);
	}
}