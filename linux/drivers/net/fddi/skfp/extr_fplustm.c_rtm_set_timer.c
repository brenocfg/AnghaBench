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
struct TYPE_4__ {TYPE_1__* a; } ;
struct s_smc {TYPE_2__ mib; } ;
struct TYPE_3__ {scalar_t__ fddiPATHT_Rmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B2_RTM_INI ; 
 int /*<<< orphan*/  DB_RMT (char*,int) ; 
 size_t PATH0 ; 
 int /*<<< orphan*/  outpd (int /*<<< orphan*/ ,scalar_t__) ; 

void rtm_set_timer(struct s_smc *smc)
{
	/*
	 * MIB timer and hardware timer have the same resolution of 80nS
	 */
	DB_RMT("RMT: setting new fddiPATHT_Rmode, t = %d ns",
	       (int)smc->mib.a[PATH0].fddiPATHT_Rmode);
	outpd(ADDR(B2_RTM_INI),smc->mib.a[PATH0].fddiPATHT_Rmode) ;
}