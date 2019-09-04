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
struct tty_struct {int count; int /*<<< orphan*/ * port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ SERIAL_TIMER_VALUE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rs_poll ; 
 int /*<<< orphan*/  serial_port ; 
 int /*<<< orphan*/  serial_timer ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_lock ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_open(struct tty_struct *tty, struct file * filp)
{
	tty->port = &serial_port;
	spin_lock_bh(&timer_lock);
	if (tty->count == 1) {
		timer_setup(&serial_timer, rs_poll, 0);
		mod_timer(&serial_timer, jiffies + SERIAL_TIMER_VALUE);
	}
	spin_unlock_bh(&timer_lock);

	return 0;
}