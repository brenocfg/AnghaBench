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
struct tty_struct {TYPE_1__* driver_data; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 TYPE_1__ tpk_port ; 
 int tty_port_open (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 

__attribute__((used)) static int tpk_open(struct tty_struct *tty, struct file *filp)
{
	tty->driver_data = &tpk_port;

	return tty_port_open(&tpk_port.port, tty, filp);
}