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
struct sym_hcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INB (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRST ; 
 int /*<<< orphan*/  nc_istat ; 
 int /*<<< orphan*/  nc_mbox1 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sym_chip_reset (struct sym_hcb *np)
{
	OUTB(np, nc_istat, SRST);
	INB(np, nc_mbox1);
	udelay(10);
	OUTB(np, nc_istat, 0);
	INB(np, nc_mbox1);
	udelay(2000);	/* For BUS MODE to settle */
}