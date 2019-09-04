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
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 int /*<<< orphan*/  PPCSTRUCT (int /*<<< orphan*/ *) ; 
 unsigned int ppc6_rd_port (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bpck6_read_regr(PIA *pi, int cont, int reg)
{
	unsigned int out;

	/* check for bad settings */
	if (reg<0 || reg>7 || cont<0 || cont>2)
	{
		return(-1);
	}
	out=ppc6_rd_port(PPCSTRUCT(pi),cont?reg|8:reg);
	return(out);
}