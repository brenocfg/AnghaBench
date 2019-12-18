#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_addr; } ;

/* Variables and functions */
 scalar_t__ DEBUG ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ pcipcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcipcwd_keepalive(void)
{
	/* Re-trigger watchdog by writing to port 0 */
	spin_lock(&pcipcwd_private.io_lock);
	outb_p(0x42, pcipcwd_private.io_addr);	/* send out any data */
	spin_unlock(&pcipcwd_private.io_lock);

	if (debug >= DEBUG)
		pr_debug("Watchdog keepalive signal send\n");

	return 0;
}