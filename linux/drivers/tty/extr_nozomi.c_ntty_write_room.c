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
struct tty_struct {struct port* driver_data; } ;
struct port {int /*<<< orphan*/  fifo_ul; } ;
struct nozomi {int dummy; } ;

/* Variables and functions */
 struct nozomi* get_dc_by_tty (struct tty_struct*) ; 
 int kfifo_avail (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ntty_write_room(struct tty_struct *tty)
{
	struct port *port = tty->driver_data;
	int room = 4096;
	const struct nozomi *dc = get_dc_by_tty(tty);

	if (dc)
		room = kfifo_avail(&port->fifo_ul);

	return room;
}