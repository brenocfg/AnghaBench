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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pids; int /*<<< orphan*/  address; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGP_EPADDR (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DBGP_GO ; 
 int DBGP_MAX_PACKET ; 
 int /*<<< orphan*/  DBGP_OUT ; 
 int /*<<< orphan*/  USB_PID_IN ; 
 int /*<<< orphan*/  dbgp_get_data (void*,int) ; 
 int /*<<< orphan*/  dbgp_len_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbgp_pid_read_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dbgp_wait_until_done (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ehci_debug ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dbgp_bulk_read(unsigned devnum, unsigned endpoint, void *data,
			  int size, int loops)
{
	u32 pids, addr, ctrl;
	int ret;

	if (size > DBGP_MAX_PACKET)
		return -1;

	addr = DBGP_EPADDR(devnum, endpoint);

	pids = readl(&ehci_debug->pids);
	pids = dbgp_pid_read_update(pids, USB_PID_IN);

	ctrl = readl(&ehci_debug->control);
	ctrl = dbgp_len_update(ctrl, size);
	ctrl &= ~DBGP_OUT;
	ctrl |= DBGP_GO;

	writel(addr, &ehci_debug->address);
	writel(pids, &ehci_debug->pids);
	ret = dbgp_wait_until_done(ctrl, loops);
	if (ret < 0)
		return ret;

	if (size > ret)
		size = ret;
	dbgp_get_data(data, size);
	return ret;
}