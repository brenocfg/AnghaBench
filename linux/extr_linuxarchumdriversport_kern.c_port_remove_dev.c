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
struct port_dev {int helper_pid; int telnetd_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_kill_process (int,int) ; 

void port_remove_dev(void *d)
{
	struct port_dev *dev = d;

	if (dev->helper_pid != -1)
		os_kill_process(dev->helper_pid, 0);
	if (dev->telnetd_pid != -1)
		os_kill_process(dev->telnetd_pid, 1);
	dev->helper_pid = -1;
	dev->telnetd_pid = -1;
}