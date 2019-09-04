#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* driver; int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct tty_port {int /*<<< orphan*/  count; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  device_name; struct tty_port port; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  mgslpc_flush_buffer (struct tty_struct*) ; 
 scalar_t__ mgslpc_paranoia_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mgslpc_wait_until_sent (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (TYPE_2__*,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_close_end (struct tty_port*,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (struct tty_port*,struct tty_struct*,struct file*) ; 
 scalar_t__ tty_port_initialized (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_tty_set (struct tty_port*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mgslpc_close(struct tty_struct *tty, struct file * filp)
{
	MGSLPC_INFO * info = (MGSLPC_INFO *)tty->driver_data;
	struct tty_port *port = &info->port;

	if (mgslpc_paranoia_check(info, tty->name, "mgslpc_close"))
		return;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_close(%s) entry, count=%d\n",
			 __FILE__, __LINE__, info->device_name, port->count);

	if (tty_port_close_start(port, tty, filp) == 0)
		goto cleanup;

	if (tty_port_initialized(port))
		mgslpc_wait_until_sent(tty, info->timeout);

	mgslpc_flush_buffer(tty);

	tty_ldisc_flush(tty);
	shutdown(info, tty);
	
	tty_port_close_end(port, tty);
	tty_port_tty_set(port, NULL);
cleanup:
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_close(%s) exit, count=%d\n", __FILE__, __LINE__,
			tty->driver->name, port->count);
}