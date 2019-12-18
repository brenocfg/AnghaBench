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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int DBGP_DONE ; 
 int DBGP_ERRCODE (int) ; 
 int DBGP_ERROR ; 
 int DBGP_LEN (int) ; 
 int DBGP_TIMEOUT ; 
 TYPE_1__* ehci_debug ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dbgp_wait_until_complete(void)
{
	u32 ctrl;
	int loop = DBGP_TIMEOUT;

	do {
		ctrl = readl(&ehci_debug->control);
		/* Stop when the transaction is finished */
		if (ctrl & DBGP_DONE)
			break;
		udelay(1);
	} while (--loop > 0);

	if (!loop)
		return -DBGP_TIMEOUT;

	/*
	 * Now that we have observed the completed transaction,
	 * clear the done bit.
	 */
	writel(ctrl | DBGP_DONE, &ehci_debug->control);
	return (ctrl & DBGP_ERROR) ? -DBGP_ERRCODE(ctrl) : DBGP_LEN(ctrl);
}