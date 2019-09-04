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
struct tty_port {int dummy; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ SERIAL_TIMER_VALUE ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct tty_port serial_port ; 
 int /*<<< orphan*/  serial_timer ; 
 scalar_t__ simc_poll (int /*<<< orphan*/ ) ; 
 int simc_read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_lock ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs_poll(struct timer_list *unused)
{
	struct tty_port *port = &serial_port;
	int i = 0;
	int rd = 1;
	unsigned char c;

	spin_lock(&timer_lock);

	while (simc_poll(0)) {
		rd = simc_read(0, &c, 1);
		if (rd <= 0)
			break;
		tty_insert_flip_char(port, c, TTY_NORMAL);
		i++;
	}

	if (i)
		tty_flip_buffer_push(port);
	if (rd)
		mod_timer(&serial_timer, jiffies + SERIAL_TIMER_VALUE);
	spin_unlock(&timer_lock);
}