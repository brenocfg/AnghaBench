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
struct tty_struct {struct ipoctal_channel* driver_data; } ;
struct ipoctal_channel {int /*<<< orphan*/  tty_port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipoctal_free_channel (struct ipoctal_channel*) ; 
 int /*<<< orphan*/  tty_port_close (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 

__attribute__((used)) static void ipoctal_close(struct tty_struct *tty, struct file *filp)
{
	struct ipoctal_channel *channel = tty->driver_data;

	tty_port_close(&channel->tty_port, tty, filp);
	ipoctal_free_channel(channel);
}