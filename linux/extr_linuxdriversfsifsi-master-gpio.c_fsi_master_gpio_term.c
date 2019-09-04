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
typedef  int /*<<< orphan*/  uint8_t ;
struct fsi_master_gpio {int /*<<< orphan*/  cmd_lock; } ;
struct fsi_master {int dummy; } ;
struct fsi_gpio_msg {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  build_term_command (struct fsi_gpio_msg*,int /*<<< orphan*/ ) ; 
 int fsi_master_gpio_xfer (struct fsi_master_gpio*,int /*<<< orphan*/ ,struct fsi_gpio_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  last_address_update (struct fsi_master_gpio*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fsi_master_gpio* to_fsi_master_gpio (struct fsi_master*) ; 

__attribute__((used)) static int fsi_master_gpio_term(struct fsi_master *_master,
		int link, uint8_t id)
{
	struct fsi_master_gpio *master = to_fsi_master_gpio(_master);
	struct fsi_gpio_msg cmd;
	int rc;

	if (link != 0)
		return -ENODEV;

	mutex_lock(&master->cmd_lock);
	build_term_command(&cmd, id);
	rc = fsi_master_gpio_xfer(master, id, &cmd, 0, NULL);
	last_address_update(master, id, false, 0);
	mutex_unlock(&master->cmd_lock);

	return rc;
}