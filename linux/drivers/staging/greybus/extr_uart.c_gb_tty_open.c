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
struct tty_struct {struct gb_tty* driver_data; } ;
struct gb_tty {int /*<<< orphan*/  port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int tty_port_open (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 

__attribute__((used)) static int gb_tty_open(struct tty_struct *tty, struct file *file)
{
	struct gb_tty *gb_tty = tty->driver_data;

	return tty_port_open(&gb_tty->port, tty, file);
}