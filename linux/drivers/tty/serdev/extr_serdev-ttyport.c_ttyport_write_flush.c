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
struct tty_struct {int dummy; } ;
struct serport {struct tty_struct* tty; } ;
struct serdev_controller {int dummy; } ;

/* Variables and functions */
 struct serport* serdev_controller_get_drvdata (struct serdev_controller*) ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 

__attribute__((used)) static void ttyport_write_flush(struct serdev_controller *ctrl)
{
	struct serport *serport = serdev_controller_get_drvdata(ctrl);
	struct tty_struct *tty = serport->tty;

	tty_driver_flush_buffer(tty);
}