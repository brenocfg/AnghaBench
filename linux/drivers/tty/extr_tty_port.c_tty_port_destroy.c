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

/* Variables and functions */
 int /*<<< orphan*/  tty_buffer_cancel_work (struct tty_port*) ; 
 int /*<<< orphan*/  tty_buffer_free_all (struct tty_port*) ; 

void tty_port_destroy(struct tty_port *port)
{
	tty_buffer_cancel_work(port);
	tty_buffer_free_all(port);
}