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

/* Variables and functions */
 int /*<<< orphan*/  ipoctal_reset_channel (struct ipoctal_channel*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipoctal_shutdown(struct tty_struct *tty)
{
	struct ipoctal_channel *channel = tty->driver_data;

	if (channel == NULL)
		return;

	ipoctal_reset_channel(channel);
	tty_port_set_initialized(&channel->tty_port, 0);
}