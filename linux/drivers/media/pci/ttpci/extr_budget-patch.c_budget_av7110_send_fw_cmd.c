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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct budget_patch {int dummy; } ;

/* Variables and functions */
 scalar_t__ COMMAND ; 
 int /*<<< orphan*/  DEBINOSWAP ; 
 int /*<<< orphan*/  dprintk (int,char*,struct budget_patch*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ttpci_budget_debiwrite (struct budget_patch*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int budget_av7110_send_fw_cmd(struct budget_patch *budget, u16* buf, int length)
{
	int i;

	dprintk(2, "budget: %p\n", budget);

	for (i = 2; i < length; i++)
	{
		  ttpci_budget_debiwrite(budget, DEBINOSWAP, COMMAND + 2*i, 2, (u32) buf[i], 0,0);
		  msleep(5);
	}
	if (length)
		  ttpci_budget_debiwrite(budget, DEBINOSWAP, COMMAND + 2, 2, (u32) buf[1], 0,0);
	else
		  ttpci_budget_debiwrite(budget, DEBINOSWAP, COMMAND + 2, 2, 0, 0,0);
	msleep(5);
	ttpci_budget_debiwrite(budget, DEBINOSWAP, COMMAND, 2, (u32) buf[0], 0,0);
	msleep(5);
	return 0;
}