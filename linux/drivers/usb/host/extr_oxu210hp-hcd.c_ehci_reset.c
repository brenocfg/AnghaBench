#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct oxu_hcd {TYPE_1__* regs; int /*<<< orphan*/  next_statechange; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESET ; 
 int /*<<< orphan*/  HC_STATE_HALT ; 
 int /*<<< orphan*/  dbg_cmd (struct oxu_hcd*,char*,int /*<<< orphan*/ ) ; 
 int handshake (struct oxu_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_2__* oxu_to_hcd (struct oxu_hcd*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdi_reset (struct oxu_hcd*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehci_reset(struct oxu_hcd *oxu)
{
	int	retval;
	u32	command = readl(&oxu->regs->command);

	command |= CMD_RESET;
	dbg_cmd(oxu, "reset", command);
	writel(command, &oxu->regs->command);
	oxu_to_hcd(oxu)->state = HC_STATE_HALT;
	oxu->next_statechange = jiffies;
	retval = handshake(oxu, &oxu->regs->command,
			    CMD_RESET, 0, 250 * 1000);

	if (retval)
		return retval;

	tdi_reset(oxu);

	return retval;
}