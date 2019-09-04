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
typedef  scalar_t__ uint8_t ;
struct fsi_master_gpio {int /*<<< orphan*/  dev; } ;
struct fsi_gpio_msg {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ FSI_RESP_ACK ; 
 int /*<<< orphan*/  build_term_command (struct fsi_gpio_msg*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  echo_delay (struct fsi_master_gpio*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int read_one_response (struct fsi_master_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  serial_out (struct fsi_master_gpio*,struct fsi_gpio_msg*) ; 

__attribute__((used)) static int issue_term(struct fsi_master_gpio *master, uint8_t slave)
{
	struct fsi_gpio_msg cmd;
	unsigned long flags;
	uint8_t tag;
	int rc;

	build_term_command(&cmd, slave);

	local_irq_save(flags);
	serial_out(master, &cmd);
	echo_delay(master);
	local_irq_restore(flags);

	rc = read_one_response(master, 0, NULL, &tag);
	if (rc < 0) {
		dev_err(master->dev,
				"TERM failed; lost communication with slave\n");
		return -EIO;
	} else if (tag != FSI_RESP_ACK) {
		dev_err(master->dev, "TERM failed; response %d\n", tag);
		return -EIO;
	}

	return 0;
}