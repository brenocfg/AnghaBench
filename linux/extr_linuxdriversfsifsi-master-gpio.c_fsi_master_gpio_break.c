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
struct fsi_master_gpio {int /*<<< orphan*/  cmd_lock; scalar_t__ external_mode; } ;
struct fsi_master {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  FSI_BREAK_CLOCKS ; 
 int /*<<< orphan*/  FSI_POST_BREAK_CLOCKS ; 
 int /*<<< orphan*/  FSI_PRE_BREAK_CLOCKS ; 
 int /*<<< orphan*/  clock_toggle (struct fsi_master_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  echo_delay (struct fsi_master_gpio*) ; 
 int /*<<< orphan*/  last_address_update (struct fsi_master_gpio*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sda_out (struct fsi_master_gpio*,int) ; 
 int /*<<< orphan*/  set_sda_output (struct fsi_master_gpio*,int) ; 
 struct fsi_master_gpio* to_fsi_master_gpio (struct fsi_master*) ; 
 int /*<<< orphan*/  trace_fsi_master_gpio_break (struct fsi_master_gpio*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int fsi_master_gpio_break(struct fsi_master *_master, int link)
{
	struct fsi_master_gpio *master = to_fsi_master_gpio(_master);
	unsigned long flags;

	if (link != 0)
		return -ENODEV;

	trace_fsi_master_gpio_break(master);

	mutex_lock(&master->cmd_lock);
	if (master->external_mode) {
		mutex_unlock(&master->cmd_lock);
		return -EBUSY;
	}

	local_irq_save(flags);

	set_sda_output(master, 1);
	sda_out(master, 1);
	clock_toggle(master, FSI_PRE_BREAK_CLOCKS);
	sda_out(master, 0);
	clock_toggle(master, FSI_BREAK_CLOCKS);
	echo_delay(master);
	sda_out(master, 1);
	clock_toggle(master, FSI_POST_BREAK_CLOCKS);

	local_irq_restore(flags);

	last_address_update(master, 0, false, 0);
	mutex_unlock(&master->cmd_lock);

	/* Wait for logic reset to take effect */
	udelay(200);

	return 0;
}