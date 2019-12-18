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
struct s_smc {int dummy; } ;
typedef  scalar_t__ HW_PTR ;

/* Variables and functions */
 scalar_t__ PLC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_CNTRL_B ; 
 int PL_MAINT ; 
 int PL_PCM_CNTRL ; 
 int /*<<< orphan*/  SK_UNUSED (struct s_smc*) ; 
 int inpw (scalar_t__) ; 
 int /*<<< orphan*/  outpw (scalar_t__,int) ; 

__attribute__((used)) static void plc_go_state(struct s_smc *smc, int p, int state)
{
	HW_PTR port ;
	int val ;

	SK_UNUSED(smc) ;

	port = (HW_PTR) (PLC(p,PL_CNTRL_B)) ;
	val = inpw(port) & ~(PL_PCM_CNTRL | PL_MAINT) ;
	outpw(port,val) ;
	outpw(port,val | state) ;
}