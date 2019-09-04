#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  mgslpc_flush_buffer (struct tty_struct*) ; 
 scalar_t__ mgslpc_paranoia_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (TYPE_1__*,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_hangup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mgslpc_hangup(struct tty_struct *tty)
{
	MGSLPC_INFO * info = (MGSLPC_INFO *)tty->driver_data;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_hangup(%s)\n",
			 __FILE__, __LINE__, info->device_name);

	if (mgslpc_paranoia_check(info, tty->name, "mgslpc_hangup"))
		return;

	mgslpc_flush_buffer(tty);
	shutdown(info, tty);
	tty_port_hangup(&info->port);
}