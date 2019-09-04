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
struct biosregs {int ah; int flags; int bx; int cx; int al; int eflags; int /*<<< orphan*/  ax; int /*<<< orphan*/  di; int /*<<< orphan*/  hsi; int /*<<< orphan*/  si; int /*<<< orphan*/  dx; int /*<<< orphan*/  ebx; } ;
struct TYPE_3__ {int cseg_16; int flags; int /*<<< orphan*/  version; int /*<<< orphan*/  dseg_len; int /*<<< orphan*/  cseg_16_len; int /*<<< orphan*/  cseg_len; int /*<<< orphan*/  dseg; int /*<<< orphan*/  offset; int /*<<< orphan*/  cseg; } ;
struct TYPE_4__ {TYPE_1__ apm_bios_info; } ;

/* Variables and functions */
 int X86_EFLAGS_CF ; 
 TYPE_2__ boot_params ; 
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,struct biosregs*) ; 

int query_apm_bios(void)
{
	struct biosregs ireg, oreg;

	/* APM BIOS installation check */
	initregs(&ireg);
	ireg.ah = 0x53;
	intcall(0x15, &ireg, &oreg);

	if (oreg.flags & X86_EFLAGS_CF)
		return -1;		/* No APM BIOS */

	if (oreg.bx != 0x504d)		/* "PM" signature */
		return -1;

	if (!(oreg.cx & 0x02))		/* 32 bits supported? */
		return -1;

	/* Disconnect first, just in case */
	ireg.al = 0x04;
	intcall(0x15, &ireg, NULL);

	/* 32-bit connect */
	ireg.al = 0x03;
	intcall(0x15, &ireg, &oreg);

	boot_params.apm_bios_info.cseg        = oreg.ax;
	boot_params.apm_bios_info.offset      = oreg.ebx;
	boot_params.apm_bios_info.cseg_16     = oreg.cx;
	boot_params.apm_bios_info.dseg        = oreg.dx;
	boot_params.apm_bios_info.cseg_len    = oreg.si;
	boot_params.apm_bios_info.cseg_16_len = oreg.hsi;
	boot_params.apm_bios_info.dseg_len    = oreg.di;

	if (oreg.flags & X86_EFLAGS_CF)
		return -1;

	/* Redo the installation check as the 32-bit connect;
	   some BIOSes return different flags this way... */

	ireg.al = 0x00;
	intcall(0x15, &ireg, &oreg);

	if ((oreg.eflags & X86_EFLAGS_CF) || oreg.bx != 0x504d) {
		/* Failure with 32-bit connect, try to disconect and ignore */
		ireg.al = 0x04;
		intcall(0x15, &ireg, NULL);
		return -1;
	}

	boot_params.apm_bios_info.version = oreg.ax;
	boot_params.apm_bios_info.flags   = oreg.cx;
	return 0;
}