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
struct pt_regs {int /*<<< orphan*/  cs; int /*<<< orphan*/  ip; } ;
struct mce {int mcgstatus; int status; int /*<<< orphan*/  cs; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int MCACOD ; 
 int MCACOD_INSTR ; 
 int MCG_STATUS_EIPV ; 
 int MCG_STATUS_RIPV ; 
 int MCI_STATUS_ADDRV ; 
 int MCI_STATUS_AR ; 
 int MCI_STATUS_EN ; 
 int MCI_STATUS_MISCV ; 
 int MCI_STATUS_OVER ; 
 int MCI_STATUS_PCC ; 
 int MCI_STATUS_S ; 
 int MCI_STATUS_UC ; 

__attribute__((used)) static void quirk_sandybridge_ifu(int bank, struct mce *m, struct pt_regs *regs)
{
	if (bank != 0)
		return;
	if ((m->mcgstatus & (MCG_STATUS_EIPV|MCG_STATUS_RIPV)) != 0)
		return;
	if ((m->status & (MCI_STATUS_OVER|MCI_STATUS_UC|
		          MCI_STATUS_EN|MCI_STATUS_MISCV|MCI_STATUS_ADDRV|
			  MCI_STATUS_PCC|MCI_STATUS_S|MCI_STATUS_AR|
			  MCACOD)) !=
			 (MCI_STATUS_UC|MCI_STATUS_EN|
			  MCI_STATUS_MISCV|MCI_STATUS_ADDRV|MCI_STATUS_S|
			  MCI_STATUS_AR|MCACOD_INSTR))
		return;

	m->mcgstatus |= MCG_STATUS_EIPV;
	m->ip = regs->ip;
	m->cs = regs->cs;
}