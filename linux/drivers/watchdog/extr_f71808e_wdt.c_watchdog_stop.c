#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  sioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  F71808FG_FLAG_WD_EN ; 
 int /*<<< orphan*/  F71808FG_REG_WDT_CONF ; 
 int /*<<< orphan*/  SIO_F71808FG_LD_WDT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  superio_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int superio_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ watchdog ; 

__attribute__((used)) static int watchdog_stop(void)
{
	int err = 0;

	mutex_lock(&watchdog.lock);
	err = superio_enter(watchdog.sioaddr);
	if (err)
		goto exit_unlock;
	superio_select(watchdog.sioaddr, SIO_F71808FG_LD_WDT);

	superio_clear_bit(watchdog.sioaddr, F71808FG_REG_WDT_CONF,
			F71808FG_FLAG_WD_EN);

	superio_exit(watchdog.sioaddr);

exit_unlock:
	mutex_unlock(&watchdog.lock);

	return err;
}