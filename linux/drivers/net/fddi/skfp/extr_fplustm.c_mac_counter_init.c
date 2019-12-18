#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_6__ {TYPE_1__* m; } ;
struct TYPE_7__ {int /*<<< orphan*/  err_stats; } ;
struct TYPE_8__ {TYPE_3__ fp; } ;
struct s_smc {TYPE_2__ mib; TYPE_4__ hw; } ;
struct err_st {int dummy; } ;
struct TYPE_5__ {scalar_t__ fddiMACRingOp_Ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_ECNTR ; 
 int /*<<< orphan*/  FM_FCNTR ; 
 int /*<<< orphan*/  FM_LCNTR ; 
 size_t MAC0 ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mac_counter_init(struct s_smc *smc)
{
	int i ;
	u_long *ec ;

	/*
	 * clear FORMAC+ frame-, lost- and error counter
	 */
	outpw(FM_A(FM_FCNTR),0) ;
	outpw(FM_A(FM_LCNTR),0) ;
	outpw(FM_A(FM_ECNTR),0) ;
	/*
	 * clear internal error counter structure
	 */
	ec = (u_long *)&smc->hw.fp.err_stats ;
	for (i = (sizeof(struct err_st)/sizeof(long)) ; i ; i--)
		*ec++ = 0L ;
	smc->mib.m[MAC0].fddiMACRingOp_Ct = 0 ;
}