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
struct tty_struct {int /*<<< orphan*/  port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int tty_port_open (int /*<<< orphan*/ ,struct tty_struct*,struct file*) ; 

__attribute__((used)) static int pti_tty_driver_open(struct tty_struct *tty, struct file *filp)
{
	/*
	 * we actually want to allocate a new channel per open, per
	 * system arch.  HW gives more than plenty channels for a single
	 * system task to have its own channel to write trace data. This
	 * also removes a locking requirement for the actual write
	 * procedure.
	 */
	return tty_port_open(tty->port, tty, filp);
}