#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int index; TYPE_1__* driver; TYPE_2__* driver_data; int /*<<< orphan*/  name; } ;
struct tty_port {int count; int low_latency; long flags; int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;
struct TYPE_7__ {int line; int device_name; struct tty_port port; int /*<<< orphan*/  netlock; scalar_t__ netcount; struct TYPE_7__* next_device; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 long ASYNC_LOW_LATENCY ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ debug_level ; 
 int mgslpc_device_count ; 
 TYPE_2__* mgslpc_device_list ; 
 scalar_t__ mgslpc_paranoia_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int startup (TYPE_2__*,struct tty_struct*) ; 
 int tty_port_block_til_ready (struct tty_port*,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  tty_port_tty_set (struct tty_port*,struct tty_struct*) ; 

__attribute__((used)) static int mgslpc_open(struct tty_struct *tty, struct file * filp)
{
	MGSLPC_INFO	*info;
	struct tty_port *port;
	int		retval, line;
	unsigned long	flags;

	/* verify range of specified line number */
	line = tty->index;
	if (line >= mgslpc_device_count) {
		printk("%s(%d):mgslpc_open with invalid line #%d.\n",
			__FILE__, __LINE__, line);
		return -ENODEV;
	}

	/* find the info structure for the specified line */
	info = mgslpc_device_list;
	while(info && info->line != line)
		info = info->next_device;
	if (mgslpc_paranoia_check(info, tty->name, "mgslpc_open"))
		return -ENODEV;

	port = &info->port;
	tty->driver_data = info;
	tty_port_tty_set(port, tty);

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_open(%s), old ref count = %d\n",
			 __FILE__, __LINE__, tty->driver->name, port->count);

	port->low_latency = (port->flags & ASYNC_LOW_LATENCY) ? 1 : 0;

	spin_lock_irqsave(&info->netlock, flags);
	if (info->netcount) {
		retval = -EBUSY;
		spin_unlock_irqrestore(&info->netlock, flags);
		goto cleanup;
	}
	spin_lock(&port->lock);
	port->count++;
	spin_unlock(&port->lock);
	spin_unlock_irqrestore(&info->netlock, flags);

	if (port->count == 1) {
		/* 1st open on this device, init hardware */
		retval = startup(info, tty);
		if (retval < 0)
			goto cleanup;
	}

	retval = tty_port_block_til_ready(&info->port, tty, filp);
	if (retval) {
		if (debug_level >= DEBUG_LEVEL_INFO)
			printk("%s(%d):block_til_ready(%s) returned %d\n",
				 __FILE__, __LINE__, info->device_name, retval);
		goto cleanup;
	}

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_open(%s) success\n",
			 __FILE__, __LINE__, info->device_name);
	retval = 0;

cleanup:
	return retval;
}