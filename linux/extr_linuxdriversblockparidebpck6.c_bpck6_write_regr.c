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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 int /*<<< orphan*/  PPCSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppc6_wr_port (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bpck6_write_regr(PIA *pi, int cont, int reg, int val)
{
	/* check for bad settings */
	if (reg>=0 && reg<=7 && cont>=0 && cont<=1)
	{
		ppc6_wr_port(PPCSTRUCT(pi),cont?reg|8:reg,(u8)val);
	}
}