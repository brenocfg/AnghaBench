#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* a; } ;
struct TYPE_11__ {TYPE_4__ group_addr; } ;
struct TYPE_9__ {int* a; } ;
struct TYPE_12__ {TYPE_5__ fp; TYPE_3__ fddi_home_addr; } ;
struct TYPE_8__ {TYPE_1__* m; } ;
struct s_smc {TYPE_6__ hw; TYPE_2__ mib; } ;
struct TYPE_7__ {long fddiMACT_Req; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_LAGC ; 
 int /*<<< orphan*/  FM_LAGL ; 
 int /*<<< orphan*/  FM_LAGM ; 
 int /*<<< orphan*/  FM_LAIC ; 
 int /*<<< orphan*/  FM_LAIL ; 
 int /*<<< orphan*/  FM_LAIM ; 
 int /*<<< orphan*/  FM_SAGP ; 
 int /*<<< orphan*/  FM_SAID ; 
 int /*<<< orphan*/  FM_TREQ0 ; 
 int /*<<< orphan*/  FM_TREQ1 ; 
 size_t MAC0 ; 
 unsigned short my_sagp ; 
 unsigned short my_said ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static	void set_formac_addr(struct s_smc *smc)
{
	long	t_requ = smc->mib.m[MAC0].fddiMACT_Req ;

	outpw(FM_A(FM_SAID),my_said) ;	/* set short address */
	outpw(FM_A(FM_LAIL),(unsigned short)((smc->hw.fddi_home_addr.a[4]<<8) +
					smc->hw.fddi_home_addr.a[5])) ;
	outpw(FM_A(FM_LAIC),(unsigned short)((smc->hw.fddi_home_addr.a[2]<<8) +
					smc->hw.fddi_home_addr.a[3])) ;
	outpw(FM_A(FM_LAIM),(unsigned short)((smc->hw.fddi_home_addr.a[0]<<8) +
					smc->hw.fddi_home_addr.a[1])) ;

	outpw(FM_A(FM_SAGP),my_sagp) ;	/* set short group address */

	outpw(FM_A(FM_LAGL),(unsigned short)((smc->hw.fp.group_addr.a[4]<<8) +
					smc->hw.fp.group_addr.a[5])) ;
	outpw(FM_A(FM_LAGC),(unsigned short)((smc->hw.fp.group_addr.a[2]<<8) +
					smc->hw.fp.group_addr.a[3])) ;
	outpw(FM_A(FM_LAGM),(unsigned short)((smc->hw.fp.group_addr.a[0]<<8) +
					smc->hw.fp.group_addr.a[1])) ;

	/* set r_request regs. (MSW & LSW of TRT ) */
	outpw(FM_A(FM_TREQ1),(unsigned short)(t_requ>>16)) ;
	outpw(FM_A(FM_TREQ0),(unsigned short)t_requ) ;
}