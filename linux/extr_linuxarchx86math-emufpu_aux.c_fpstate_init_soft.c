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
struct swregs_state {int cwd; int twd; int no_update; int /*<<< orphan*/  fip; int /*<<< orphan*/  foo; scalar_t__ ftop; scalar_t__ swd; } ;
struct address {scalar_t__ opcode; scalar_t__ selector; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct swregs_state*,int /*<<< orphan*/ ,int) ; 

void fpstate_init_soft(struct swregs_state *soft)
{
	struct address *oaddr, *iaddr;
	memset(soft, 0, sizeof(*soft));
	soft->cwd = 0x037f;
	soft->swd = 0;
	soft->ftop = 0;	/* We don't keep top in the status word internally. */
	soft->twd = 0xffff;
	/* The behaviour is different from that detailed in
	   Section 15.1.6 of the Intel manual */
	oaddr = (struct address *)&soft->foo;
	oaddr->offset = 0;
	oaddr->selector = 0;
	iaddr = (struct address *)&soft->fip;
	iaddr->offset = 0;
	iaddr->selector = 0;
	iaddr->opcode = 0;
	soft->no_update = 1;
}