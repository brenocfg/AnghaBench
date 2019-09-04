#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* driver_data; } ;
struct tty_port {struct tty_struct* tty; int /*<<< orphan*/  count; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct tty_port port; } ;
typedef  TYPE_1__ modem_info ;
struct TYPE_5__ {int /*<<< orphan*/  modempoll; } ;

/* Variables and functions */
 TYPE_3__* dev ; 
 int isdn_tty_startup (TYPE_1__*) ; 
 int tty_port_block_til_ready (struct tty_port*,struct tty_struct*,struct file*) ; 

__attribute__((used)) static int
isdn_tty_open(struct tty_struct *tty, struct file *filp)
{
	modem_info *info = tty->driver_data;
	struct tty_port *port = &info->port;
	int retval;

#ifdef ISDN_DEBUG_MODEM_OPEN
	printk(KERN_DEBUG "isdn_tty_open %s, count = %d\n", tty->name,
	       port->count);
#endif
	port->count++;
	port->tty = tty;
	/*
	 * Start up serial port
	 */
	retval = isdn_tty_startup(info);
	if (retval) {
#ifdef ISDN_DEBUG_MODEM_OPEN
		printk(KERN_DEBUG "isdn_tty_open return after startup\n");
#endif
		return retval;
	}
	retval = tty_port_block_til_ready(port, tty, filp);
	if (retval) {
#ifdef ISDN_DEBUG_MODEM_OPEN
		printk(KERN_DEBUG "isdn_tty_open return after isdn_tty_block_til_ready \n");
#endif
		return retval;
	}
#ifdef ISDN_DEBUG_MODEM_OPEN
	printk(KERN_DEBUG "isdn_tty_open ttyi%d successful...\n", info->line);
#endif
	dev->modempoll++;
#ifdef ISDN_DEBUG_MODEM_OPEN
	printk(KERN_DEBUG "isdn_tty_open normal exit\n");
#endif
	return 0;
}