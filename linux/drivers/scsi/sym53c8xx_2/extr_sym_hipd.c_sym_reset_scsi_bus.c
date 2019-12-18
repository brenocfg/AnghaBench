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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u32 ;
struct sym_hcb {int rv_dcntl; int features; int /*<<< orphan*/  maxwide; } ;

/* Variables and functions */
 int CRST ; 
 int FE_WIDE ; 
 int INB (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int INW (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int IRQM ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTW (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RST ; 
 int SYM_SETUP_SCSI_BUS_CHECK ; 
 int TE ; 
 int /*<<< orphan*/  nc_dcntl ; 
 int /*<<< orphan*/  nc_mbox1 ; 
 int /*<<< orphan*/  nc_sbcl ; 
 int /*<<< orphan*/  nc_sbdl ; 
 int /*<<< orphan*/  nc_scntl1 ; 
 int /*<<< orphan*/  nc_sien ; 
 int /*<<< orphan*/  nc_sstat0 ; 
 int /*<<< orphan*/  nc_sstat2 ; 
 int /*<<< orphan*/  nc_stest3 ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* sym_name (struct sym_hcb*) ; 
 int /*<<< orphan*/  sym_soft_reset (struct sym_hcb*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int sym_reset_scsi_bus(struct sym_hcb *np, int enab_int)
{
	u32 term;
	int retv = 0;

	sym_soft_reset(np);	/* Soft reset the chip */
	if (enab_int)
		OUTW(np, nc_sien, RST);
	/*
	 *  Enable Tolerant, reset IRQD if present and 
	 *  properly set IRQ mode, prior to resetting the bus.
	 */
	OUTB(np, nc_stest3, TE);
	OUTB(np, nc_dcntl, (np->rv_dcntl & IRQM));
	OUTB(np, nc_scntl1, CRST);
	INB(np, nc_mbox1);
	udelay(200);

	if (!SYM_SETUP_SCSI_BUS_CHECK)
		goto out;
	/*
	 *  Check for no terminators or SCSI bus shorts to ground.
	 *  Read SCSI data bus, data parity bits and control signals.
	 *  We are expecting RESET to be TRUE and other signals to be 
	 *  FALSE.
	 */
	term =	INB(np, nc_sstat0);
	term =	((term & 2) << 7) + ((term & 1) << 17);	/* rst sdp0 */
	term |= ((INB(np, nc_sstat2) & 0x01) << 26) |	/* sdp1     */
		((INW(np, nc_sbdl) & 0xff)   << 9)  |	/* d7-0     */
		((INW(np, nc_sbdl) & 0xff00) << 10) |	/* d15-8    */
		INB(np, nc_sbcl);	/* req ack bsy sel atn msg cd io    */

	if (!np->maxwide)
		term &= 0x3ffff;

	if (term != (2<<7)) {
		printf("%s: suspicious SCSI data while resetting the BUS.\n",
			sym_name(np));
		printf("%s: %sdp0,d7-0,rst,req,ack,bsy,sel,atn,msg,c/d,i/o = "
			"0x%lx, expecting 0x%lx\n",
			sym_name(np),
			(np->features & FE_WIDE) ? "dp1,d15-8," : "",
			(u_long)term, (u_long)(2<<7));
		if (SYM_SETUP_SCSI_BUS_CHECK == 1)
			retv = 1;
	}
out:
	OUTB(np, nc_scntl1, 0);
	return retv;
}