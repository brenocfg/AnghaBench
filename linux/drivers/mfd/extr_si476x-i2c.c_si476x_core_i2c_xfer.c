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
struct si476x_core {int /*<<< orphan*/  client; } ;
typedef  enum si476x_i2c_type { ____Placeholder_si476x_i2c_type } si476x_i2c_type ;

/* Variables and functions */
 int SI476X_I2C_SEND ; 
 int /*<<< orphan*/  SI476X_MAX_IO_ERRORS ; 
 int i2c_master_recv (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  si476x_core_pronounce_dead (struct si476x_core*) ; 

int si476x_core_i2c_xfer(struct si476x_core *core,
		    enum si476x_i2c_type type,
		    char *buf, int count)
{
	static int io_errors_count;
	int err;
	if (type == SI476X_I2C_SEND)
		err = i2c_master_send(core->client, buf, count);
	else
		err = i2c_master_recv(core->client, buf, count);

	if (err < 0) {
		if (io_errors_count++ > SI476X_MAX_IO_ERRORS)
			si476x_core_pronounce_dead(core);
	} else {
		io_errors_count = 0;
	}

	return err;
}