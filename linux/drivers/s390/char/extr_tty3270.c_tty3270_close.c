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
struct tty_struct {int count; struct tty3270* driver_data; } ;
struct tty3270 {int /*<<< orphan*/  port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_port_tty_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tty3270_close(struct tty_struct *tty, struct file * filp)
{
	struct tty3270 *tp = tty->driver_data;

	if (tty->count > 1)
		return;
	if (tp)
		tty_port_tty_set(&tp->port, NULL);
}